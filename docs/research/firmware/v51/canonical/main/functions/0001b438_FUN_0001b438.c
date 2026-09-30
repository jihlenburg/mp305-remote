/* Address: 0001b438; name: FUN_0001b438; body bytes: 82 */

void FUN_0001b438(void)

{
  int iVar1;
  
  if (DAT_1fff9b9b == '\x02') {
    iVar1 = (DAT_1fffa968 + 500) / 1000;
    if ((iVar1 < 0) || (DAT_1fff9ba1 != '\0')) {
      iVar1 = 0;
    }
    DAT_1fffa950 = (int)(iVar1 * (uint)DAT_1fffaa0e) / 50000 + DAT_1fff9b5a / 10;
    DAT_1fffa954 = DAT_1fff9b5e + 500;
  }
  else {
    DAT_1fffa954 = 0;
    DAT_1fffa950 = 0;
  }
  return;
}

