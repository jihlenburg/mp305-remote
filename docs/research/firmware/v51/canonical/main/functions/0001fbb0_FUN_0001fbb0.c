/* Address: 0001fbb0; name: FUN_0001fbb0; body bytes: 180 */

void FUN_0001fbb0(void)

{
  ushort uVar1;
  uint uVar2;
  byte bVar3;
  undefined4 extraout_r2;
  int extraout_r2_00;
  uint extraout_r3;
  
  DAT_1fffaa5f = FUN_0001a100();
  DAT_1fffaa80 = FUN_0001a140();
  DAT_1fffaa88 = FUN_0001a10c();
  DAT_1fffaa8c = (int)((uint)DAT_1fffaa80 * (uint)DAT_1fffaa88) / 1000;
  uVar1 = DAT_1fffaa80;
  if ((DAT_1fffaaac != '\0') && (DAT_1fffaa5c != '\0')) {
    uVar1 = DAT_1fffaa82;
    DAT_1fffaa84 = DAT_1fffaa88;
  }
  DAT_1fffaa82 = uVar1;
  if (DAT_1fffaa60 != 0) {
    DAT_1fffaa68 = DAT_1fffaa80 / DAT_1fffaa60;
    DAT_1fffaa6a = DAT_1fffaa80 / DAT_1fffaa60;
    DAT_1fffaa6c = DAT_1fffaa68 - DAT_1fffaa6a;
  }
  bVar3 = DAT_1fffaaad;
  if (5 < DAT_1fffaaad) {
    bVar3 = 1;
  }
  FUN_00015460(bVar3);
  uVar2 = FUN_00015474(extraout_r2);
  uVar2 = (DAT_1fffaa80 / uVar2 + DAT_1fffaa80 / extraout_r3 + 1 & 0x1ffff) >> 1;
  if (extraout_r2_00 == 5) {
    if (0x14 < uVar2) {
      uVar2 = 0x14;
    }
  }
  else if (extraout_r2_00 == 4) {
    if (0xc < uVar2) {
      uVar2 = 0xc;
    }
  }
  else if (extraout_r2_00 == 3) {
    if (8 < uVar2) {
      uVar2 = 8;
    }
  }
  else if (6 < uVar2) {
    uVar2 = 6;
  }
  DAT_1fffaa61 = (char)uVar2;
  return;
}

