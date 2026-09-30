// Recover RAM copies directly described by the vendor SDK startup.
// @category MP305
import ghidra.app.script.GhidraScript;
import ghidra.program.model.mem.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import java.io.*;
import java.nio.file.*;
import java.math.BigInteger;
public class RefineSdk extends GhidraScript{
 void copy(String name,long src,long dst,int n,boolean x)throws Exception{byte[] b=new byte[n];currentProgram.getMemory().getBytes(toAddr(src),b);MemoryBlock m=currentProgram.getMemory().createInitializedBlock(name,toAddr(dst),new ByteArrayInputStream(b),n,monitor,false);m.setWrite(true);m.setExecute(x);}
 public void run()throws Exception{
  Memory mem=currentProgram.getMemory();mem.removeBlock(mem.getBlock(toAddr(0x20000000L)),monitor);
  mem.createUninitializedBlock("SDK_vectors",toAddr(0x20000000L),0x10,false).setWrite(true);
  copy("SDK_RAM_startup",0x40280,0x20000010L,0x30,true);copy("SDK_RAM_code",0x402b0,0x20000040L,0x1878,true);copy("SDK_RAM_data",0x6c668,0x200018b8L,0x118,false);
  mem.createUninitializedBlock("SDK_BSS",toAddr(0x200019d0L),0xe630,false).setWrite(true);
  currentProgram.getProgramContext().setValue(currentProgram.getRegister("gp"),toAddr(0x40000),toAddr(0x6c77f),BigInteger.valueOf(0x20004000L));
  currentProgram.getProgramContext().setValue(currentProgram.getRegister("gp"),toAddr(0x20000000L),toAddr(0x2000ffffL),BigInteger.valueOf(0x20004000L));
  for(String line:Files.readAllLines(Path.of(getScriptArgs()[0]))){if(line.startsWith("slot"))continue;String[]c=line.split("\t");long a=Long.parseLong(c[1],16);if(c[2].equals("VER_LIB"))continue;disassemble(toAddr(a));Function f=getFunctionAt(toAddr(a));if(f==null)f=createFunction(toAddr(a),c[2]);if(f!=null)f.setName(c[2],SourceType.USER_DEFINED);}
  for(Function f:currentProgram.getFunctionManager().getFunctions(true))if(f.getEntryPoint().getOffset()>=0x20000010L && f.getEntryPoint().getOffset()<0x200018b8L)disassemble(f.getEntryPoint());
  analyzeAll(currentProgram);
 }
}
