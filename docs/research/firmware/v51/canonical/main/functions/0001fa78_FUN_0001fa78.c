/* Address: 0001fa78; name: FUN_0001fa78; body bytes: 100 */

void FUN_0001fa78(int param_1)

{
  if (DAT_1fffaa5e != '\0') {
    DAT_1fffaa98 = (uint)DAT_1fffaa88 * param_1 + DAT_1fffaa98;
    DAT_1fffaa9c = DAT_1fffaa8c * param_1 + DAT_1fffaa9c;
    if (3600000 < DAT_1fffaa98) {
      DAT_1fffaa90 = DAT_1fffaa98 / 3600000 + DAT_1fffaa90;
      DAT_1fffaa98 = DAT_1fffaa98 % 3600000;
    }
    if (3600000 < DAT_1fffaa9c) {
      DAT_1fffaa94 = DAT_1fffaa9c / 3600000 + DAT_1fffaa94;
      DAT_1fffaa9c = DAT_1fffaa9c % 3600000;
    }
  }
  if ((uint)DAT_1fffaa7e < DAT_1fffaa90 / 10) {
    DAT_1fffaa7e = (ushort)(DAT_1fffaa90 / 10);
  }
  return;
}

