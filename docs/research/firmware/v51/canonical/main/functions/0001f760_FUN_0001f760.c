/* Address: 0001f760; name: FUN_0001f760; body bytes: 94 */

uint FUN_0001f760(uint param_1)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  
  uVar1 = (uint)DAT_1fffaa88;
  uVar2 = param_1;
  if ('8' < DAT_1fffaa5f) {
    bVar3 = DAT_1fffaa62 + 1;
    uVar2 = uVar1;
    if (DAT_1fffaa5f < '<') {
      DAT_1fffaa62 = bVar3;
      if (bVar3 < 0x10) goto LAB_0001f7b0;
      uVar1 = uVar1 * 0x69;
    }
    else {
      if ((DAT_1fffaa5f < '@') || (DAT_1fffaa62 = bVar3, bVar3 < 0xb)) goto LAB_0001f7b0;
      uVar1 = uVar1 * 0x5f;
    }
    DAT_1fffaa62 = 0;
    uVar2 = uVar1 / 100 & 0xffff;
  }
LAB_0001f7b0:
  if (uVar2 < 100) {
    uVar2 = 100;
  }
  if (param_1 < uVar2) {
    uVar2 = param_1;
  }
  return uVar2;
}

