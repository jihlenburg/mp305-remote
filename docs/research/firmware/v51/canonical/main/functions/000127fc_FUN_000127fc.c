/* Address: 000127fc; name: FUN_000127fc; body bytes: 62 */

void FUN_000127fc(void)

{
  undefined4 *puVar1;
  
  if (DAT_1ffe04f4 != 0) {
    if (DAT_1fffab18 == '\x01') {
      puVar1 = &DAT_1ffe0528;
    }
    else if (DAT_1fffab18 == '\x02') {
      puVar1 = &DAT_1ffe052c;
    }
    else {
      if (DAT_1fffab18 != '\x03') {
        return;
      }
      puVar1 = &DAT_1ffe0530;
    }
    FUN_0004e5a6(*puVar1,7,0);
  }
  DAT_1fffab18 = 0;
  return;
}

