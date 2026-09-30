// Seed repeated absolute call targets in the 8051 image, keeping a review trail.
// @category MP305
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import java.io.*;
import java.util.*;
public class Discover8051Calls extends GhidraScript{
 public void run()throws Exception{
  Map<Long,List<Long>> candidates=new TreeMap<>();
  for(long p=0x1000;p<0xb01f;p++){
   if((getByte(toAddr(p))&255)!=0x12)continue;
   long a=((getByte(toAddr(p+1))&255)<<8)|(getByte(toAddr(p+2))&255);
   if(a>=0x1000 && a<0xb022)candidates.computeIfAbsent(a,k->new ArrayList<>()).add(p);
  }
  int count=0;
  try(PrintWriter out=new PrintWriter(getScriptArgs()[0])){
   out.println("target\traw_lcall_candidates\tcreated\tsource_addresses");
   for(Map.Entry<Long,List<Long>> e:candidates.entrySet()){
    long a=e.getKey();if(e.getValue().size()<3 || getFunctionAt(toAddr(a))!=null)continue;
    // Do not split existing functions based only on byte-pattern evidence.
    if(currentProgram.getFunctionManager().getFunctionContaining(toAddr(a))!=null)continue;
    disassemble(toAddr(a));Function f=createFunction(toAddr(a),null);
    if(f!=null){count++;f.setComment("Inferred entry from "+e.getValue().size()+" raw LCALL encodings. Review control flow before relying on semantics.");}
    out.printf("%04x\t%d\t%s\t%s%n",a,e.getValue().size(),f!=null,e.getValue());
   }
  }
  println("Created 8051 call-target functions: "+count);analyzeAll(currentProgram);
 }
}
