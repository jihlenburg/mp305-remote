// Apply reviewed labels, keeping evidence and uncertainty in comments.
// @category MP305
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import java.nio.file.*;
public class ApplyAnnotations extends GhidraScript{
 public void run()throws Exception{
  for(MemoryBlock b:currentProgram.getMemory().getBlocks())if(!b.isInitialized() && (b.getStart().getOffset()>=0x1ffe0000L))b.setWrite(true);
  for(String line:Files.readAllLines(Path.of(getScriptArgs()[0]))){
   if(line.startsWith("kind")||line.isBlank())continue;String[]c=line.split("\t",4);Address a=toAddr(Long.parseLong(c[1],16));
   if(c[0].equals("function")){Function f=getFunctionAt(a);if(f==null){disassemble(a);f=createFunction(a,c[2]);}if(f!=null){f.setName(c[2],SourceType.USER_DEFINED);f.setComment(c[3]);}}
   else{createLabel(a,c[2],true);currentProgram.getListing().setComment(a,CodeUnit.PLATE_COMMENT,c[3]);}
  }
  analyzeAll(currentProgram);
 }
}
