/* Address: 00019f4c; name: FUN_00019f4c; body bytes: 112 */

void FUN_00019f4c(void)

{
  int iVar1;
  
  DAT_1fffa960 = FUN_00015fbc();
  iVar1 = FUN_000159e4();
  if ((iVar1 == 0) && (DAT_1fffaa37 == '\x02')) {
    DAT_1fffa960 = DAT_1fffa960 + DAT_1fffa960 / 100;
  }
  DAT_1fffa964 = (DAT_1fffa960 + 5) / 10;
  DAT_1fffa970 = FUN_00016024();
  DAT_1fffa96c = DAT_1fffa970 - (uint)(DAT_1fffa964 * 0xd0) / 10000;
  if (DAT_1fffa96c < 0) {
    DAT_1fffa96c = 0;
  }
  DAT_1fffa968 = FUN_00010388((int)((longlong)DAT_1fffa96c * 1000000),
                              (int)((ulonglong)((longlong)DAT_1fffa96c * 1000000) >> 0x20),
                              DAT_1fffa938,0);
  FUN_00016c6a(6);
  return;
}

