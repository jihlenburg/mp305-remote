// Restore runtime mappings proven by startup copy loops.
// @category MP305
import ghidra.app.script.GhidraScript;
import ghidra.program.model.mem.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import java.io.ByteArrayInputStream;
import java.math.BigInteger;
public class RefineFirmware extends GhidraScript {
 void seed(long p,String name) throws Exception {disassemble(toAddr(p));if(getFunctionAt(toAddr(p))==null)createFunction(toAddr(p),name);if(name!=null && getFunctionAt(toAddr(p))!=null)getFunctionAt(toAddr(p)).setName(name,SourceType.USER_DEFINED);}
 void copy(String name,long src,long dst,int n,boolean execute)throws Exception {
  byte[] b=new byte[n];currentProgram.getMemory().getBytes(toAddr(src),b);
  MemoryBlock m=currentProgram.getMemory().createInitializedBlock(name,toAddr(dst),new ByteArrayInputStream(b),n,monitor,false);m.setRead(true);m.setWrite(true);m.setExecute(execute);
 }
 public void run()throws Exception{
  String kind=getScriptArgs()[0];Memory mem=currentProgram.getMemory();mem.getBlock(toAddr(kind.equals("arm")?0x10000:0x1000)).setWrite(false);
  if(kind.equals("arm")){
   if(mem.getBlock(toAddr(0x1ffe0000L))==null)mem.createUninitializedBlock("SRAM_lower",toAddr(0x1ffe0000L),0x10000,false);
   long[] a={0x15430,0x1fff0,0x10ee4,0x533c0,0x1db74};String[] n={"encode_transport_frame","append_stuffed_byte","runtime_scatter_init","application_main","SystemInit"};
   for(int i=0;i<a.length;i++)seed(a[i],n[i]);
  }else if(kind.equals("riscv")){
   mem.removeBlock(mem.getBlock(toAddr(0x20000000L)),monitor);
   mem.createUninitializedBlock("SRAM_reserved",toAddr(0x20000000L),0x2000,false);
   copy("RAM_code_and_vectors",0x1008,0x20002000L,0xc40,true);
   copy("RAM_data",0x9318,0x20002c40L,0x310,false);
   mem.createUninitializedBlock("BSS_and_stack",toAddr(0x20002f50L),0xd0b0,false);
   currentProgram.getProgramContext().setValue(currentProgram.getRegister("gp"),toAddr(0x1000),toAddr(0x967f),BigInteger.valueOf(0x20002000L));
   currentProgram.getProgramContext().setValue(currentProgram.getRegister("gp"),toAddr(0x20002000L),toAddr(0x20002c3fL),BigInteger.valueOf(0x20002000L));
   seed(0x1c48,"runtime_start");seed(0x7794,"application_main");
   for(long p=0x20002000L;p<0x200020c6L;p+=4){long v=Integer.toUnsignedLong(getInt(toAddr(p)));if((v&1)==0 && ((v>=0x200020c6L && v<0x20002c40L)||(v>=0x1c48 && v<0x8e68)))seed(v,null);}
   for(Function f:currentProgram.getFunctionManager().getFunctions(true))if(f.getEntryPoint().getOffset()>=0x200020c6L && f.getEntryPoint().getOffset()<0x20002c40L)disassemble(f.getEntryPoint());
  }else if(kind.equals("8051")){
   for(long p=0x1003;p<=0x104b;p+=8)seed(p,null);
  }
  analyzeAll(currentProgram);
 }
}
