/* Address: ram:00046806; name: FUN_ram_00046806; body bytes: 62 */

undefined4 FUN_ram_00046806(uint param_1)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if (DAT_ram_20001a04 == (byte *)0x0) {
    uVar1 = 0x12;
  }
  else {
    uVar1 = 3;
    if (*DAT_ram_20001a04 == param_1) {
      tmos_stop_task(DAT_ram_20001d4c,1);
      FUN_ram_000461a2(0x30);
      uVar1 = FUN_ram_0004588a(0);
      return uVar1;
    }
  }
  return uVar1;
}

