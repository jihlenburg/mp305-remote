// Import initial SRAM recovered by emulating the original scatter loader.
// @category MP305
import ghidra.app.script.GhidraScript;
import ghidra.program.model.mem.*;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import java.io.*;
public class FinalizeMain extends GhidraScript {
 public void run()throws Exception{
  Memory mem=currentProgram.getMemory();MemoryBlock lower=mem.getBlock(toAddr(0x1ffe0000L));mem.removeBlock(lower,monitor);
  MemoryBlock b=mem.createInitializedBlock("initialized_data",toAddr(0x1ffe0000L),new FileInputStream(getScriptArgs()[0]),0xb5c,monitor,false);b.setWrite(true);b.setExecute(false);
  mem.createUninitializedBlock("BSS_lower",toAddr(0x1ffe0b5cL),0xf4a4,false);
  // Four-byte literals are constant flash data, but the bootloader below 0x10000 is absent.
  long[] a={0x11652,0x202cc};String[] n={"scatter_decompress_data","scatter_zero_bss"};
  for(int i=0;i<a.length;i++){if(getFunctionAt(toAddr(a[i]))==null){disassemble(toAddr(a[i]));createFunction(toAddr(a[i]),n[i]);}else getFunctionAt(toAddr(a[i])).setName(n[i],SourceType.USER_DEFINED);}
  analyzeAll(currentProgram);
 }
}
