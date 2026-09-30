// Correct a data pointer initially seeded as code in the supplementary SDK.
// @category MP305
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
public class CleanupSdk extends GhidraScript{
 public void run()throws Exception{
  Function f=getFunctionAt(toAddr(0x6c278));if(f!=null)currentProgram.getFunctionManager().removeFunction(toAddr(0x6c278));
  clearListing(toAddr(0x6c278),toAddr(0x6c28f));
  createAsciiString(toAddr(0x6c278));
 }
}
