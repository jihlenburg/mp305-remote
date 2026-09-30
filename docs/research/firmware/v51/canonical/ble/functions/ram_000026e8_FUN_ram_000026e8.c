/* Address: ram:000026e8; name: FUN_ram_000026e8; body bytes: 66 */

int FUN_ram_000026e8(void)

{
  int iVar1;
  
  gp = &DAT_ram_20002000;
  if ((DAT_ram_40001008 & 0x40) == 0) {
    iVar1 = 0x1e85000;
  }
  else {
    if ((DAT_ram_40001008 & 0xc0) != 0x40) {
      return 32000;
    }
    iVar1 = 0x1c9c4000;
  }
  if ((DAT_ram_40001008 & 0x1f) == 0) {
    iVar1 = -1;
  }
  else {
    iVar1 = (iVar1 + -0x800) / (int)(DAT_ram_40001008 & 0x1f);
  }
  return iVar1;
}

