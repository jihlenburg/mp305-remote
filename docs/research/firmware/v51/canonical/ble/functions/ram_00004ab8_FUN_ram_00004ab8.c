/* Address: ram:00004ab8; name: FUN_ram_00004ab8; body bytes: 92 */

void FUN_ram_00004ab8(uint param_1)

{
  gp = &DAT_ram_20002000;
  if (DAT_ram_20002fb8 == 0) {
    return;
  }
  if (param_1 < DAT_ram_20002fb6) {
    param_1 = DAT_ram_20002fb6 - param_1;
    DAT_ram_20002fb6 = (ushort)(param_1 * 0x10000 >> 0x10);
    if ((param_1 & 0xffff) != 0) {
      gp = &DAT_ram_20002000;
      return;
    }
  }
  else {
    DAT_ram_20002fb6 = 0;
  }
  if (DAT_ram_20002fb8 != 1) {
    DAT_ram_20002fb8 = 0;
    return;
  }
  FUN_ram_0000566a();
  FUN_ram_000074bc();
  DAT_ram_20002fb8 = 0;
  return;
}

