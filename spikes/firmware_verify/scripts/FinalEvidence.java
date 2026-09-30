// Save symbols, memory mappings, and data references for inspection outside Ghidra.
// @category MP305
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.mem.*;
import java.io.*;
public class FinalEvidence extends GhidraScript{
 public void run()throws Exception{
  File dir=new File(getScriptArgs()[0]);dir.mkdirs();
  try(PrintWriter out=new PrintWriter(new File(dir,"memory.tsv"))){out.println("name\tstart\tend\tinitialized\twritable\texecutable");for(MemoryBlock b:currentProgram.getMemory().getBlocks())out.printf("%s\t%s\t%s\t%s\t%s\t%s%n",b.getName(),b.getStart(),b.getEnd(),b.isInitialized(),b.isWrite(),b.isExecute());}
  try(PrintWriter out=new PrintWriter(new File(dir,"symbols.tsv"))){out.println("address\tname\ttype\tsource");for(Symbol s:currentProgram.getSymbolTable().getAllSymbols(true))out.printf("%s\t%s\t%s\t%s%n",s.getAddress(),s.getName(),s.getSymbolType(),s.getSource());}
  try(PrintWriter out=new PrintWriter(new File(dir,"data-references.tsv"))){out.println("from\tto\ttype");for(Data d:currentProgram.getListing().getDefinedData(true))for(Reference r:d.getReferencesFrom())out.printf("%s\t%s\t%s%n",r.getFromAddress(),r.getToAddress(),r.getReferenceType());}
 }
}
