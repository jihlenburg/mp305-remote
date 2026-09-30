/* Address: 0001f808; name: FUN_0001f808; body bytes: 116 */

void FUN_0001f808(uint param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  if (DAT_1fffaaad != '\x05') {
    uVar3 = (uint)DAT_1fffaa68;
    uVar2 = (uint)DAT_1fffaa72;
    if (param_1 < DAT_1fffaaa8) {
      DAT_1fffaaa8 = DAT_1fffaaa8 - param_1;
    }
    else {
      DAT_1fffaaa8 = 100;
      if (uVar3 < uVar2 + 5) {
        if ((uVar3 + 5 <= uVar2) &&
           (uVar1 = ((uint)DAT_1fffaa78 * 0x65) / 100, DAT_1fffaa78 = (ushort)uVar1,
           (uVar1 & 0xffff) == 0)) {
          DAT_1fffaa78 = 1;
        }
      }
      else {
        DAT_1fffaa78 = (ushort)(((uint)DAT_1fffaa78 * 0x62) / 100);
      }
    }
    if (uVar3 < uVar2) {
      return;
    }
    if (DAT_1fffaa7e < DAT_1fffaa78) {
      return;
    }
    if (DAT_1fffaaa0 < 0x3e9) {
      return;
    }
  }
  DAT_1fffaaac = 6;
  return;
}

