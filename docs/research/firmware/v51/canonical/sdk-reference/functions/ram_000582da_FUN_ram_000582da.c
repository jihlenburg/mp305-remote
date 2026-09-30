/* Address: ram:000582da; name: FUN_ram_000582da; body bytes: 90 */

char FUN_ram_000582da(byte *param_1)

{
  char cVar1;
  uint uVar2;
  
  gp = 0x20004000;
  cVar1 = '\0';
  uVar2 = 0;
  do {
    if ((1 << (uVar2 & 0x1f) &
        (uint)param_1[1] * 0x100 + (uint)param_1[2] * 0x10000 + (uint)*param_1 +
        (uint)param_1[3] * 0x1000000) != 0) {
      cVar1 = cVar1 + '\x01';
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 != 0x20);
  uVar2 = 0;
  do {
    if (((int)(param_1[4] & 0x1f) >> (uVar2 & 0x1f) & 1U) != 0) {
      cVar1 = cVar1 + '\x01';
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 != 8);
  return cVar1;
}

