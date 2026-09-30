// Analyze the vendor reference separately from the MP305 firmware.
// @category MP305
import ghidra.app.script.GhidraScript;
import ghidra.program.model.mem.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import java.nio.file.*;
public class SupplementSdk extends GhidraScript {
 public void run()throws Exception{
  currentProgram.getMemory().getBlocks()[0].setWrite(false);currentProgram.getMemory().getBlocks()[0].setExecute(true);
  currentProgram.getMemory().createUninitializedBlock("SRAM",toAddr(0x20000000L),0x10000,false).setWrite(true);
  currentProgram.getMemory().createUninitializedBlock("peripherals",toAddr(0x40000000L),0x20000,false).setWrite(true);
  disassemble(toAddr(0x40000));createFunction(toAddr(0x40000),"sdk_entry");
  for(String line:Files.readAllLines(Path.of(getScriptArgs()[0]))){
   if(line.startsWith("slot"))continue;String[] c=line.split("\t");long a=Long.parseLong(c[1],16);if(c[2].equals("VER_LIB"))continue;if(a<0x40000 || a>=0x70000)continue;
   disassemble(toAddr(a));Function f=getFunctionAt(toAddr(a));if(f==null)f=createFunction(toAddr(a),c[2]);if(f!=null)f.setName(c[2],SourceType.USER_DEFINED);
  }
 }
}
