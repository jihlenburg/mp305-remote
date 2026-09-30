/* Address: ram:00003d0c; name: FUN_ram_00003d0c; body bytes: 126 */

void FUN_ram_00003d0c(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  
  gp = &DAT_ram_20002000;
  if (DAT_ram_20003a4a < 5) {
    FUN_ram_000078b2(&DAT_ram_20003644 + (uint)DAT_ram_20003a4d * 0x100,param_1,param_2);
    uVar1 = DAT_ram_20003a4d + 1;
    (&DAT_ram_20003a44)[DAT_ram_20003a4d] = (char)param_2;
    if ((uVar1 & 0xff) < 4) {
      DAT_ram_20003a4d = (byte)uVar1;
    }
    else {
      DAT_ram_20003a4d = 0;
    }
    DAT_ram_20003a4a = DAT_ram_20003a4a + 1;
    return;
  }
  return;
}

