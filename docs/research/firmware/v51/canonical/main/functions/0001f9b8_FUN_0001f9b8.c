/* Address: 0001f9b8; name: FUN_0001f9b8; body bytes: 98 */

void FUN_0001f9b8(void)

{
  uint uVar1;
  
  uVar1 = get_output_faults();
  DAT_1fffaab0 = uVar1 | DAT_1fffaab0;
  if ((DAT_1fffaa88 < 0xb) &&
     (((int)(DAT_1fffaa7a - 10) <= (int)(uint)DAT_1fffaa80 || (DAT_1fffaa80 < 0x1f5)))) {
    DAT_1fffaa65 = DAT_1fffaa65 + 1;
    if (5 < DAT_1fffaa65) {
      DAT_1fffaab0 = DAT_1fffaab0 | 0x400;
    }
  }
  else {
    DAT_1fffaa65 = 0;
    DAT_1fffaab0 = DAT_1fffaab0 & 0xfffffbff;
  }
  if (DAT_1fffaab0 == 0) {
    return;
  }
  if ((DAT_1fffaaac == '\x05') || (DAT_1fffaaac == '\x06')) {
    DAT_1fffaab0 = DAT_1fffaab0 & 0xfffffbff;
  }
  FUN_0001d858();
  return;
}

