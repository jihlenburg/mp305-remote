/* Address: ram:0006b13c; name: GAPRole_PeripheralStartDevice; body bytes: 108 */

undefined4 GAPRole_PeripheralStartDevice(undefined1 param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  DAT_ram_20001d51 = param_1;
  if (param_2 != 0) {
    FUN_ram_00069bd6(param_2);
  }
  if (DAT_ram_20001f20 == 0) {
    if (param_3 != 0) {
      DAT_ram_20001abc = param_3;
    }
    uVar1 = FUN_ram_000484e0(DAT_ram_200019cc,DAT_ram_20001f48,DAT_ram_20001ac0,&DAT_ram_20001f28,
                             &DAT_ram_20001f38,&DAT_ram_20001acc);
    return uVar1;
  }
  return 0x11;
}

