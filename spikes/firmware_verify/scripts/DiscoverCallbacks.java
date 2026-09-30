// Recover functions reachable through stored pointers, recording every seed.
// @category MP305
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.listing.*;
import java.io.*;
import java.util.*;
public class DiscoverCallbacks extends GhidraScript{
 public void run()throws Exception{
  Set<Long> seen=new HashSet<>();int created=0;
  try(PrintWriter out=new PrintWriter(getScriptArgs()[0])){
   out.println("pointer_location\ttarget\tmethod\tcreated");
   for(MemoryBlock b:currentProgram.getMemory().getBlocks()){
    if(!b.isInitialized())continue;
    for(long p=b.getStart().getOffset();p+3<=b.getEnd().getOffset();p+=4){
     long value=Integer.toUnsignedLong(getInt(toAddr(p)));if((value&1)==0)continue;long target=value&~1L;
     if(target<0x10358 || target>=0x70000 || !seen.add(target))continue;
     Address a=toAddr(target);if(currentProgram.getFunctionManager().getFunctionContaining(a)!=null)continue;
     int h=getShort(a)&65535;
     boolean prologue=(h&0xff00)==0xb500 || h==0xe92d;
     if(!prologue && getInstructionAt(a)==null)continue;
     boolean did=disassemble(a);Function f=getFunctionAt(a);if(f==null && did)f=createFunction(a,null);
     if(f!=null){f.setComment("Recovered from stored Thumb pointer at "+toAddr(p)+"; callback identification is inferred until reviewed.");created++;}
     out.printf("%08x\t%08x\t%s\t%s%n",p,target,prologue?"pointer_and_prologue":"pointer_and_existing_instruction",f!=null);
    }
   }
  }
  println("Created pointer-referenced functions: "+created);analyzeAll(currentProgram);
 }
}
