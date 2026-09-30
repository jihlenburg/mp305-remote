/* Address: 0001d868; name: FUN_0001d868; body bytes: 222 */

void FUN_0001d868(void)

{
  uint uVar1;
  uint uVar2;
  
  DAT_1fffa0b8 = 0x40;
  DAT_1fffa0b9 = 5;
  if (DAT_1ffe01cc == '\0') {
    DAT_1fffa124 = 0;
    DAT_1fffa128 = 0;
    DAT_1fffa12c = 0;
    DAT_1fffa0ce = 0;
    if (DAT_1ffe01cd == '\0') {
      DAT_1fffa0d0 = 0x3ed;
      DAT_1fffa120 = 0;
      DAT_1fffa0d2 = 0;
    }
  }
  DAT_1fffa0bf = 0;
  DAT_1fffa0d4 = 0x14a;
  DAT_1fffa0d6 = 1000;
  DAT_1fffa0c1 = 1;
  DAT_1fffa0c2 = 1;
  DAT_1fffa0c3 = 3;
  DAT_1fffa0c4 = 0;
  DAT_1fffa0c5 = 0;
  DAT_1fffa0c6 = 0;
  DAT_1fffa0f8 = 0x14a;
  DAT_1fffa0fa = 1000;
  DAT_1fffa0fc = 500;
  DAT_1fffa0fe = 1000;
  DAT_1fffa100 = 1000;
  DAT_1fffa102 = 2000;
  DAT_1fffa104 = 0x5dc;
  DAT_1fffa106 = 3000;
  DAT_1fffa108 = 2000;
  DAT_1fffa10a = 5000;
  DAT_1fffa10c = 3000;
  DAT_1fffa10e = 5000;
  uVar2 = 6;
  do {
    (&DAT_1fffa0f8)[uVar2 * 2] = 0;
    uVar1 = uVar2 + 1 & 0xff;
    (&DAT_1fffa0fa)[uVar2 * 2] = 0;
    uVar2 = uVar1;
  } while (uVar1 < 10);
  DAT_1fffa0c7 = 5;
  DAT_1fffa0dc = DAT_1ffe07d4;
  DAT_1fffa0e0 = DAT_1ffe07d8;
  DAT_1fffa0e4 = DAT_1ffe07dc;
  uVar2 = 0;
  do {
    uVar1 = uVar2 + 1 & 0xff;
    (&DAT_1fffa0e8)[uVar2] = 1000;
    uVar2 = uVar1;
  } while (uVar1 < 6);
  uVar2 = 0;
  do {
    uVar1 = uVar2 + 1 & 0xff;
    (&DAT_1fffa0c8)[uVar2] = 1;
    uVar2 = uVar1;
  } while (uVar1 < 6);
  DAT_1fffa0cf = 0;
  DAT_1fffa0c0 = 0;
  DAT_1fffa0f6 = 0;
  DAT_1fffa130 = 1000000;
  FUN_00014638();
  FUN_0001c364();
  return;
}

