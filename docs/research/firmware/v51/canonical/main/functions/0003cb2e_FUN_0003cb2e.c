/* Address: 0003cb2e; name: FUN_0003cb2e; body bytes: 62 */

int FUN_0003cb2e(uint param_1,uint param_2,uint param_3)

{
  if (10000 < param_1) {
    param_1 = 0x27f6;
  }
  if (10000 < param_2) {
    param_2 = 0x27f6;
  }
  if (10000 < param_3) {
    param_3 = 0x27f6;
  }
  return (param_1 + 5) / 10 + ((param_3 + 5) / 10) * 0x100000 + ((param_2 + 5) / 10) * 0x400 +
         -0x80000000;
}

