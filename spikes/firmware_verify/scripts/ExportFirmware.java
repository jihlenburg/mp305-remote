// Export decompiler output and its address-linked supporting evidence.
// @category MP305
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
public class ExportFirmware extends GhidraScript {
 public void run() throws Exception {
  File dir=new File(getScriptArgs()[0]);dir.mkdirs();File funcs=new File(dir,"functions");funcs.mkdirs();
  DecompInterface d=new DecompInterface();DecompileOptions opts=new DecompileOptions();opts.setRespectReadOnly(true);d.setOptions(opts);d.openProgram(currentProgram);
  int count=0,ok=0;
  try(PrintWriter index=new PrintWriter(new File(dir,"functions.tsv"));PrintWriter all=new PrintWriter(new File(dir,"decompiled.c"));PrintWriter calls=new PrintWriter(new File(dir,"calls.tsv"));PrintWriter refs=new PrintWriter(new File(dir,"references.tsv"));PrintWriter asm=new PrintWriter(new File(dir,"listing.asm"))){
   index.println("address\tname\tbody_bytes\tdecompiled\tmessage");calls.println("caller\tcallee\tcallee_name");refs.println("from\tto\ttype");
   for(Function f:currentProgram.getFunctionManager().getFunctions(true)){
    if(monitor.isCancelled())break;count++;
    DecompileResults r=d.decompileFunction(f,45,monitor);String code;
    if(r.decompileCompleted() && r.getDecompiledFunction()!=null){ok++;code=r.getDecompiledFunction().getC();}else code="/* Decompilation failed: "+r.getErrorMessage()+" */";
    String address=f.getEntryPoint().toString();String header="/* Address: "+address+"; name: "+f.getName()+"; body bytes: "+f.getBody().getNumAddresses()+" */\n";
    try(PrintWriter one=new PrintWriter(new File(funcs,address+"_"+f.getName().replaceAll("[^A-Za-z0-9_]","_")+".c"))){one.print(header);one.print(code);}
    all.print(header);all.println(code);
    index.printf("%s\t%s\t%d\t%s\t%s%n",address,f.getName(),f.getBody().getNumAddresses(),r.decompileCompleted(),r.getErrorMessage().replace('\n',' '));
    for(Function c:f.getCalledFunctions(monitor))calls.printf("%s\t%s\t%s%n",address,c.getEntryPoint(),c.getName());
    if(count%200==0)println("Exported "+count+" functions");
   }
   for(Instruction i:currentProgram.getListing().getInstructions(true)){
    StringBuilder bytes=new StringBuilder();for(byte b:i.getBytes())bytes.append(String.format("%02x",b&255));
    asm.printf("%s  %-16s  %s%n",i.getAddress(),bytes,i);
    for(Reference r:i.getReferencesFrom())refs.printf("%s\t%s\t%s%n",r.getFromAddress(),r.getToAddress(),r.getReferenceType());
   }
  }
  try(PrintWriter stats=new PrintWriter(new File(dir,"summary.txt"))){stats.printf("program=%s%nprocessor=%s%nfunctions=%d%ndecompiled=%d%n",currentProgram.getName(),currentProgram.getLanguageID(),count,ok);}
  d.dispose();println("DONE functions="+count+" decompiled="+ok);
 }
}
