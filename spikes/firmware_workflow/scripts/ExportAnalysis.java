// Export reusable Ghidra analysis metadata without any memory contents.
// Args: output-directory [candidate-input-file ...]. Firmware stays external.
import ghidra.app.script.GhidraScript;
import ghidra.app.util.xml.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.framework.options.Options;
import com.google.gson.*;
import java.nio.file.*;
import java.security.MessageDigest;
import java.util.*;

public class ExportAnalysis extends GhidraScript {
    String sha(byte[] b) throws Exception {
        return HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(b));
    }
    int locate(byte[] whole, byte[] part) {
        outer: for (int i=0;i<=whole.length-part.length;i++) {
            if (whole[i]!=part[0]) continue;
            for (int j=1;j<part.length;j++) if (whole[i+j]!=part[j]) continue outer;
            return i;
        }
        return -1;
    }
    public void run() throws Exception {
        String[] args=getScriptArgs(); Path out=Paths.get(args[0]);Files.createDirectories(out);
        XmlProgramOptions options=new XmlProgramOptions();
        options.setMemoryContents(false);
        println(new ProgramXmlMgr(out.resolve("analysis.xml").toFile()).write(currentProgram,currentProgram.getMemory(),monitor,options).toString());
        JsonObject root=new JsonObject(); root.addProperty("schema",1);
        root.addProperty("program",currentProgram.getName());
        root.addProperty("language",currentProgram.getLanguageID().toString());
        root.addProperty("compiler_spec",currentProgram.getCompilerSpec().getCompilerSpecID().toString());
        root.addProperty("executable_sha256",currentProgram.getExecutableSHA256());
        root.addProperty("memory_contents_exported",false);
        Map<String,byte[]> inputs=new LinkedHashMap<>();
        for (int i=1;i<args.length;i++) inputs.put(args[i],Files.readAllBytes(Paths.get(args[i])));
        JsonArray blocks=new JsonArray(); int unresolved=0;
        for (MemoryBlock b:currentProgram.getMemory().getBlocks()) {
            JsonObject row=new JsonObject();row.addProperty("name",b.getName());
            row.addProperty("start",b.getStart().toString());row.addProperty("length",b.getSize());
            row.addProperty("read",b.isRead());row.addProperty("write",b.isWrite());row.addProperty("execute",b.isExecute());
            row.addProperty("volatile",b.isVolatile());row.addProperty("initialized",b.isInitialized());
            row.addProperty("comment",b.getComment());
            if (b.isInitialized()) {
                byte[] bytes=b.getData().readAllBytes();row.addProperty("sha256",sha(bytes));boolean found=false;
                for (Map.Entry<String,byte[]> e:inputs.entrySet()) {
                    int offset=locate(e.getValue(),bytes);
                    if (offset>=0) {
                        row.addProperty("source_name",Paths.get(e.getKey()).getFileName().toString());
                        row.addProperty("source_sha256",sha(e.getValue()));row.addProperty("source_offset",offset);
                        found=true;break;
                    }
                }
                if (!found) {
                    boolean zero=true;for (byte v:bytes) if (v!=0) {zero=false;break;}
                    if (zero) row.addProperty("fill",0); else {unresolved++;row.addProperty("unresolved",true);}
                }
            }
            blocks.add(row);
        }
        root.add("memory_blocks",blocks);
        JsonArray funcs=new JsonArray();
        for (Function f:currentProgram.getFunctionManager().getFunctions(true)) {
            JsonObject row=new JsonObject();row.addProperty("entry",f.getEntryPoint().toString());
            row.addProperty("name",f.getName());row.addProperty("prototype",f.getPrototypeString(true,true));
            row.addProperty("signature_source",f.getSignatureSource().toString());
            row.addProperty("no_return",f.hasNoReturn());row.addProperty("inline",f.isInline());
            row.addProperty("calling_convention",f.getCallingConventionName());
            row.addProperty("call_fixup",f.getCallFixup());
            row.addProperty("comment",f.getComment());row.addProperty("repeatable_comment",f.getRepeatableComment());
            row.addProperty("custom_variable_storage",f.hasCustomVariableStorage());
            JsonArray variables=new JsonArray();
            for (Variable v:f.getAllVariables()) {
                JsonObject var=new JsonObject();var.addProperty("name",v.getName());
                var.addProperty("datatype",v.getDataType().getPathName());var.addProperty("storage",v.getVariableStorage().toString());
                var.addProperty("source",v.getSource().toString());var.addProperty("comment",v.getComment());
                var.addProperty("first_use_offset",v.getFirstUseOffset());variables.add(var);
            }
            row.add("variables",variables);
            MessageDigest bytesDigest=MessageDigest.getInstance("SHA-256");StringBuilder mnemonics=new StringBuilder();int instructionCount=0;
            for (Instruction ins:currentProgram.getListing().getInstructions(f.getBody(),true)) {
                bytesDigest.update(ins.getBytes());mnemonics.append(ins.getMnemonicString()).append('\n');instructionCount++;
            }
            row.addProperty("instruction_count",instructionCount);
            row.addProperty("instruction_bytes_sha256",HexFormat.of().formatHex(bytesDigest.digest()));
            row.addProperty("mnemonics_sha256",sha(mnemonics.toString().getBytes(java.nio.charset.StandardCharsets.UTF_8)));
            if (f.isThunk()) row.addProperty("thunk_target",f.getThunkedFunction(false).getEntryPoint().toString());
            JsonArray ranges=new JsonArray();
            for (AddressRange range:f.getBody().getAddressRanges()) {
                JsonArray pair=new JsonArray();pair.add(range.getMinAddress().toString());pair.add(range.getMaxAddress().toString());ranges.add(pair);
            }
            row.add("body",ranges);funcs.add(row);
        }
        root.add("functions",funcs);
        JsonObject groups=new JsonObject();
        for (String group:currentProgram.getOptionsNames()) {
            Options opts=currentProgram.getOptions(group);JsonObject values=new JsonObject();
            for (String name:opts.getOptionNames()) {
                JsonObject v=new JsonObject();v.addProperty("type",opts.getType(name).toString());
                v.add("value",new Gson().toJsonTree(opts.getObject(name,null)));values.add(name,v);
            }
            groups.add(group,values);
        }
        root.add("options",groups);
        Files.writeString(out.resolve("program.json"),new GsonBuilder().setPrettyPrinting().create().toJson(root)+"\n");
        println("ANALYSIS_EXPORTED functions="+funcs.size()+" unresolved_blocks="+unresolved+" memory_contents=false");
    }
}
