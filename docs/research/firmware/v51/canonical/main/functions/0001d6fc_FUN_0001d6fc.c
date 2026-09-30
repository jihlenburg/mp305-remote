/* Address: 0001d6fc; name: FUN_0001d6fc; body bytes: 158 */

void FUN_0001d6fc(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  uint uVar2;
  
  DAT_1fffaaad = (char)((uint)param_2 >> 0x10);
  DAT_1fffaa6e = (ushort)((uint)param_1 >> 0x10);
  DAT_1fffaa70 = (ushort)param_2;
  DAT_1fffaa60 = (byte)param_1;
  FUN_0001fa20();
  FUN_0001fae4();
  if (DAT_1fffaab0 == 0) {
    if (DAT_1fffaaad == '\x05') {
      DAT_1fffaa60 = 0x14;
      DAT_1fffaabc = DAT_1fffaa70;
      DAT_1fffaab4 = 0;
      DAT_1fffaac4 = DAT_1fffaab0;
      DAT_1fffaac0 = DAT_1fffaab0;
      DAT_1fffaab8 = 0;
      DAT_1fffaaba = 0;
      DAT_1fffaac8 = 30000;
      DAT_1fffaab5 = 0;
      if (0xc < DAT_1fffaa70 - 3) {
        DAT_1fffaabc = 8;
      }
    }
    DAT_1fffaa62 = 0;
    DAT_1fffaa63 = 0;
    DAT_1fffaa64 = 0;
    DAT_1fffaa65 = 0;
    DAT_1fffaa98 = DAT_1fffaab0;
    DAT_1fffaa9c = DAT_1fffaab0;
    DAT_1fffaa90 = DAT_1fffaab0;
    DAT_1fffaa94 = DAT_1fffaab0;
    DAT_1fffaaa0 = DAT_1fffaab0;
    uVar1 = DAT_1fffaa6e / 10;
    uVar2 = DAT_1fffaa6e / 10;
    DAT_1fffaa7c = (undefined2)uVar1;
    DAT_1fffaa7e = (undefined2)uVar2;
    if (uVar1 < 100) {
      DAT_1fffaa7c = 100;
    }
    if (uVar2 < 100) {
      DAT_1fffaa7e = 100;
    }
    DAT_1fffaa7a = (ushort)DAT_1fffaa60 * DAT_1fffaa72 + 100;
    DAT_1fffaa78 = 100;
    DAT_1fffaaac = 1;
    DAT_1fffaa5c = 1;
  }
  return;
}

