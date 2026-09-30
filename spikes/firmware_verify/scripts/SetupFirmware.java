// Set up the independently restored images for offline analysis.
// @category MP305
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.symbol.SourceType;
import java.math.BigInteger;
public class SetupFirmware extends GhidraScript {
 void region(String name,long start,long size) throws Exception {
  if(currentProgram.getMemory().getBlock(toAddr(start))==null){
   MemoryBlock b=currentProgram.getMemory().createUninitializedBlock(name,toAddr(start),size,false); b.setRead(true);b.setWrite(true);b.setExecute(false);
  }
 }
 void seed(long a,String name) throws Exception {
  Address p=toAddr(a); if(!currentProgram.getMemory().contains(p))return;
  disassemble(p); if(getFunctionAt(p)==null)createFunction(p,name);
  if(getFunctionAt(p)!=null && name!=null)getFunctionAt(p).setName(name,SourceType.USER_DEFINED);
 }
 public void run() throws Exception {
  String kind=getScriptArgs()[0];
  currentProgram.getMemory().getBlocks()[0].setExecute(true);
  if(kind.equals("arm")){
   currentProgram.getProgramContext().setValue(currentProgram.getRegister("TMode"),toAddr(0x10000),toAddr(0x843ff),BigInteger.ONE);
   region("SRAM",0x1fff0000L,0x50000);region("peripherals",0x40000000L,0x200000);region("cortex_system",0xe0000000L,0x100000);
   for(int i=1;i<128;i++){
    long v=Integer.toUnsignedLong(getInt(toAddr(0x10000+i*4)));
    if((v&1)!=0 && v>=0x10000 && v<0x84400)seed(v&~1L,i==1?"Reset_Handler":null);
   }
   long[] offsets={0x2f34,0x58bc,0x5ef8,0xcaa4,0xb7f4,0xb634,0xdffc,0x16a8,0x8368,0x5aa0,0x4660,0x855c,0x5bec,0xc628,0x5e48,0xc8b8,0xc73c,0x565c,0x5694,0x3c40,0xb4d0,0x5630,0xd520,0x54ac,0x555c,0x3d44,0xb7c4,0x5118,0xf508,0xf250,0x2400,0xdb94};
   String[] names={"dispatch_command","cmd_c2_telemetry","cmd_c4_read_settings","cmd_c6_write_settings","cmd_c8_dc_control","cmd_e0_device_info","cmd_00","cmd_20","cmd_a2_language","cmd_bb","cmd_bd","cmd_be","cmd_d0","cmd_d2","cmd_d4","cmd_d6","cmd_da","cmd_dc","cmd_de","handle_e1","cmd_e2","cmd_e4","cmd_e8","cmd_ea","cmd_ec","cmd_ee","cmd_f0","cmd_f2","cmd_f4","cmd_f6","cmd_fc","cmd_fe"};
   for(int i=0;i<offsets.length;i++)seed(0x10000+offsets[i],names[i]);
   createLabel(toAddr(0x1fffaaccL),"device_state",true);
  }else if(kind.equals("8051")){
   seed(0x1000,"image_entry");seed(0xaf88,"runtime_start");
  }else if(kind.equals("riscv")){
   region("SRAM",0x20000000L,0x20000);region("peripherals",0x40000000L,0x10000);region("system",0xe000e000L,0x2000);
   seed(0x1000,"image_entry");
  }
 }
}
