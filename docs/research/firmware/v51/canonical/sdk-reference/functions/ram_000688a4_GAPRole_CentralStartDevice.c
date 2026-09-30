/* Address: ram:000688a4; name: GAPRole_CentralStartDevice; body bytes: 102 */

undefined4 GAPRole_CentralStartDevice(undefined1 param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  DAT_ram_20001d52 = param_1;
  if (param_2 != 0) {
    FUN_ram_00069c04(param_2);
  }
  if (param_3 != 0) {
    DAT_ram_20001a80 = param_3;
  }
  if (DAT_ram_20001f17 == '\0') {
    uVar1 = FUN_ram_000484e0(DAT_ram_20001a7c,8,DAT_ram_20001ac0,&DAT_ram_20001f28,&DAT_ram_20001f38
                             ,&DAT_ram_20001acc);
    return uVar1;
  }
  return 0;
}

