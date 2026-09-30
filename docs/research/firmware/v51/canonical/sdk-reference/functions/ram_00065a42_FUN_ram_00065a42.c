/* Address: ram:00065a42; name: FUN_ram_00065a42; body bytes: 88 */

uint FUN_ram_00065a42(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  gp = 0x20004000;
  if (DAT_ram_20001d6c == 0) {
    DAT_ram_20001d6c = 0x7fff;
  }
  uVar4 = (uint)DAT_ram_20001d6c;
  uVar3 = 0xe;
  uVar2 = 0;
  do {
    uVar1 = uVar3 & 0x1f;
    uVar5 = (uVar4 & 0x7fff) << 1;
    uVar3 = uVar3 - 1;
    uVar2 = uVar2 | (int)(uVar4 & 0x4000) >> uVar1 & 0xffU;
    uVar4 = uVar5 | (int)uVar5 >> 0xe & 1U ^ (uVar4 & 0x7fff) >> 0xe;
  } while (uVar3 != 6);
  DAT_ram_20001d6c = (short)uVar4;
  return uVar2;
}

