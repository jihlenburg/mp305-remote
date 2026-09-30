/* Address: 0001c364; name: FUN_0001c364; body bytes: 76 */

void FUN_0001c364(void)

{
  FUN_000146e8(1);
  FUN_00014954(0x7f,1);
  if (0x3f < DAT_1fffa0b8) {
    FUN_00014878(0xfe000);
    DAT_1fffa0b8 = 0;
  }
  DAT_1fffa134 = FUN_00015f5c();
  FUN_00014738((uint)DAT_1fffa0b8 * 0x80 + 0xfe000,&DAT_1fffa0b8,0x80);
  FUN_00014954(0x7f,0);
  FUN_000146e8(0);
  return;
}

