/* Address: ram:00068974; name: FUN_ram_00068974; body bytes: 46 */

void FUN_ram_00068974(undefined1 param_1)

{
  gp = 0x20004000;
  DAT_ram_20001f52 = param_1;
  if (DAT_ram_200019cc != -1) {
    DAT_ram_20001f17 = 1;
    DAT_ram_20001f48 = 0xc;
  }
  return;
}

