/* Address: ram:000659f4; name: FUN_ram_000659f4; body bytes: 78 */

uint FUN_ram_000659f4(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  gp = 0x20004000;
  if (DAT_ram_20001d6a == 0) {
    DAT_ram_20001d6a = 0x1ff;
  }
  uVar4 = (uint)DAT_ram_20001d6a;
  uVar3 = 8;
  uVar2 = 0;
  do {
    uVar1 = uVar3 & 0x1f;
    uVar5 = (uVar4 & 0x7fff) << 1;
    uVar3 = uVar3 - 1;
    uVar2 = uVar2 | (int)(uVar4 & 0x100) >> uVar1 & 0xffU;
    uVar4 = uVar5 | ((int)uVar5 >> 9 ^ (int)uVar5 >> 5) & 1U;
  } while (uVar3 != 0);
  DAT_ram_20001d6a = (short)uVar4;
  return uVar2;
}

