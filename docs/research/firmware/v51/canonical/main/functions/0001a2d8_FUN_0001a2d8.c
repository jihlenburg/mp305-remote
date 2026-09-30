/* Address: 0001a2d8; name: FUN_0001a2d8; body bytes: 214 */

void FUN_0001a2d8(void)

{
  uint uVar1;
  
  FUN_0001b74c();
  DAT_1fffa9cc = 5000;
  DAT_1fffaa1e = 0;
  DAT_1fffaa54 = 0;
  DAT_1fffaa37 = DAT_1fffa0bf;
  DAT_1fffaa47 = 0;
  DAT_1fffaa44 = 0;
  DAT_1fffaa46 = 0;
  DAT_1fffa9f6 = 0;
  DAT_1fffa980 = 0;
  DAT_1fffa978 = 0;
  DAT_1fffaa4d = 0;
  DAT_1fffaa4e = 0;
  DAT_1fffa9b0 = 0xffffffff;
  DAT_1fffa9d8 = DAT_1fffa0d0;
  DAT_1fffa9d6 = ((ushort)DAT_1fffa0ba + (ushort)DAT_1fffa0ba * 4) * 2;
  DAT_1fffa994 = DAT_1fffa120;
  DAT_1fffaa23 = (char)((DAT_1fffa0d0 + 5) / 10);
  DAT_1fffaa1a = DAT_1fffa0d8;
  DAT_1fffaa1c = DAT_1fffa0da;
  DAT_1fffaa36 = DAT_1fffa0c4;
  DAT_1fffaa0e = DAT_1fffa0f4;
  DAT_1fffa9dc = (short)(DAT_1fffa124 / 1000);
  DAT_1fffa988 = 0;
  DAT_1fffaa50 = 0;
  DAT_1fffaa41 = 0;
  DAT_1fffaa52 = DAT_1fffa0cf;
  DAT_1fffa934 = 100000;
  if (DAT_1fffa130 - 900000U < 0x30d41) {
    DAT_1fffa938 = DAT_1fffa130;
  }
  else {
    DAT_1fffa938 = 1000000;
  }
  uVar1 = (uint)DAT_1fffa0bc;
  if (3 < uVar1) {
    uVar1 = 3;
  }
  DAT_1fffa0b1 = (&stack0xfffffff8)[uVar1];
  DAT_1fffa130 = DAT_1fffa938;
  return;
}

