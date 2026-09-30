// Restore analysis onto separately supplied, hash-checked firmware bytes.
// Args: snapshot-directory input-map.json. Use a new, disposable project.
import ghidra.app.script.GhidraScript;
import ghidra.app.util.xml.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.SourceType;
import ghidra.framework.options.Options;
import com.google.gson.*;
import java.nio.file.*;
import java.io.*;
import java.security.MessageDigest;
import java.util.*;

public class ImportAnalysis extends GhidraScript {
    String sha(byte[] b) throws Exception {return HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(b));}
    Address address(String text) {return currentProgram.getAddressFactory().getAddress(text);}
    public void run() throws Exception {
        String[] args=getScriptArgs();Path dir=Paths.get(args[0]);
        JsonObject spec=JsonParser.parseString(Files.readString(dir.resolve("program.json"))).getAsJsonObject();
        JsonObject map=JsonParser.parseString(Files.readString(Paths.get(args[1]))).getAsJsonObject();
        if (spec.get("memory_contents_exported").getAsBoolean()) throw new IllegalArgumentException("Snapshot must omit firmware contents");
        if (!currentProgram.getLanguageID().toString().equals(spec.get("language").getAsString())) throw new IllegalArgumentException("Language mismatch");
        // Validate all bytes before modifying the new project.
        Map<String,byte[]> buffers=new HashMap<>();
        for (JsonElement elem:spec.getAsJsonArray("memory_blocks")) {
            JsonObject row=elem.getAsJsonObject();if (!row.get("initialized").getAsBoolean()) continue;
            byte[] data;
            if (row.has("fill")) {data=new byte[row.get("length").getAsInt()];Arrays.fill(data,row.get("fill").getAsByte());}
            else {
                String hash=row.get("source_sha256").getAsString();
                byte[] source=Files.readAllBytes(Paths.get(map.get(hash).getAsString()));
                if (!sha(source).equals(hash)) throw new IllegalArgumentException("Input hash mismatch");
                int off=row.get("source_offset").getAsInt(),len=row.get("length").getAsInt();
                if (off<0 || off+len>source.length) throw new IllegalArgumentException("Input range invalid");
                data=Arrays.copyOfRange(source,off,off+len);
            }
            if (!sha(data).equals(row.get("sha256").getAsString())) throw new IllegalArgumentException("Block hash mismatch");
            buffers.put(row.get("start").getAsString(),data);
        }
        Memory mem=currentProgram.getMemory();
        for (MemoryBlock block:mem.getBlocks()) mem.removeBlock(block,monitor);
        for (JsonElement elem:spec.getAsJsonArray("memory_blocks")) {
            JsonObject row=elem.getAsJsonObject();String start=row.get("start").getAsString();
            String name=row.get("name").getAsString();long size=row.get("length").getAsLong();
            MemoryBlock block=row.get("initialized").getAsBoolean()
                ?mem.createInitializedBlock(name,address(start),new ByteArrayInputStream(buffers.get(start)),size,monitor,false)
                :mem.createUninitializedBlock(name,address(start),size,false);
            block.setRead(row.get("read").getAsBoolean());block.setWrite(row.get("write").getAsBoolean());
            block.setExecute(row.get("execute").getAsBoolean());block.setVolatile(row.get("volatile").getAsBoolean());
            if (row.has("comment"))block.setComment(row.get("comment").getAsString());
        }
        XmlProgramOptions options=new XmlProgramOptions();options.setMemoryContents(false);options.setMemoryBlocks(false);options.setAddToProgram(true);
        println(new ProgramXmlMgr(dir.resolve("analysis.xml").toFile()).read(currentProgram,monitor,options).toString());
        // XML import can infer extra functions or thunks and widen their bodies.
        // Reconcile the explicit entry set before restoring exact body ranges.
        FunctionManager fm=currentProgram.getFunctionManager();
        Set<Address> entries=new HashSet<>();
        for (JsonElement elem:spec.getAsJsonArray("functions")) entries.add(address(elem.getAsJsonObject().get("entry").getAsString()));
        List<Address> extras=new ArrayList<>();
        for (Function f:fm.getFunctions(true)) if (!entries.contains(f.getEntryPoint())) extras.add(f.getEntryPoint());
        for (Address entry:extras) fm.removeFunction(entry);
        for (Function f:fm.getFunctions(true)) {
            if (f.isThunk()) f.setThunkedFunction(null);
            f.setBody(new AddressSet(f.getEntryPoint()));
        }
        for (JsonElement elem:spec.getAsJsonArray("functions")) {
            JsonObject row=elem.getAsJsonObject();Address entry=address(row.get("entry").getAsString());
            if (fm.getFunctionAt(entry)==null) {
                // One archived SDK placeholder shares an address with defined
                // data. Preserve that original inconsistency explicitly.
                Data conflict=currentProgram.getListing().getDefinedDataAt(entry);
                ghidra.program.model.data.DataType type=conflict==null?null:conflict.getDataType();
                int length=conflict==null?0:conflict.getLength();
                if(conflict!=null) currentProgram.getListing().clearCodeUnits(entry,conflict.getMaxAddress(),false);
                fm.createFunction(row.get("name").getAsString(),entry,new AddressSet(entry),SourceType.IMPORTED);
                if(type!=null) currentProgram.getListing().createData(entry,type,length);
            }
        }
        for (JsonElement elem:spec.getAsJsonArray("functions")) {
            JsonObject row=elem.getAsJsonObject();Function f=getFunctionAt(address(row.get("entry").getAsString()));
            if (f==null)throw new IllegalStateException("Missing function "+row.get("entry"));
            if (!f.getName().equals(row.get("name").getAsString())) f.setName(row.get("name").getAsString(),f.getSymbol().getSource());
            f.setNoReturn(row.get("no_return").getAsBoolean());f.setInline(row.get("inline").getAsBoolean());
            f.setSignatureSource(SourceType.valueOf(row.get("signature_source").getAsString()));
            if (row.has("comment")) f.setComment(row.get("comment").getAsString());
            if (row.has("repeatable_comment")) f.setRepeatableComment(row.get("repeatable_comment").getAsString());
            if (row.has("custom_variable_storage"))f.setCustomVariableStorage(row.get("custom_variable_storage").getAsBoolean());
            AddressSet body=new AddressSet();
            for (JsonElement range:row.getAsJsonArray("body")) {JsonArray pair=range.getAsJsonArray();body.add(address(pair.get(0).getAsString()),address(pair.get(1).getAsString()));}
            f.setBody(body);
            if (row.has("call_fixup")) f.setCallFixup(row.get("call_fixup").getAsString());
        }
        for (JsonElement elem:spec.getAsJsonArray("functions")) {
            JsonObject row=elem.getAsJsonObject();
            if (row.has("thunk_target")) getFunctionAt(address(row.get("entry").getAsString())).setThunkedFunction(getFunctionAt(address(row.get("thunk_target").getAsString())));
        }
        int restoredOptions=0;
        for (Map.Entry<String,JsonElement> group:spec.getAsJsonObject("options").entrySet()) {
            Options dest=currentProgram.getOptions(group.getKey());
            for (Map.Entry<String,JsonElement> option:group.getValue().getAsJsonObject().entrySet()) {
                JsonObject row=option.getValue().getAsJsonObject();JsonElement value=row.get("value");if(value==null||value.isJsonNull())continue;
                String name=option.getKey();
                switch(row.get("type").getAsString()) {
                    case "BOOLEAN_TYPE":dest.setBoolean(name,value.getAsBoolean());break;
                    case "STRING_TYPE":dest.setString(name,value.getAsString());break;
                    case "INT_TYPE":dest.setInt(name,value.getAsInt());break;
                    case "LONG_TYPE":dest.setLong(name,value.getAsLong());break;
                    case "DOUBLE_TYPE":dest.setDouble(name,value.getAsDouble());break;
                    case "FLOAT_TYPE":dest.setFloat(name,value.getAsFloat());break;
                    default:continue;
                }
                restoredOptions++;
            }
        }
        println("ANALYSIS_RESTORED functions="+currentProgram.getFunctionManager().getFunctionCount()+" primitive_options="+restoredOptions);
    }
}
