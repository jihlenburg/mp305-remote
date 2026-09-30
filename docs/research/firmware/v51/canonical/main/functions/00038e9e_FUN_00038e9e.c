/* Address: 00038e9e; name: FUN_00038e9e; body bytes: 68 */

void FUN_00038e9e(undefined4 param_1,uint param_2)

{
  byte bVar1;
  
  FUN_00038e78(param_1,2);
  bVar1 = 0;
  do {
    if ((int)(param_2 << 0x18) < 0) {
      FUN_00038e6e();
    }
    else {
      FUN_00038e66(param_1);
    }
    FUN_000144fc(5);
    FUN_00038e40(param_1);
    FUN_000144fc(5);
    FUN_00038e38(param_1);
    bVar1 = bVar1 + 1;
    param_2 = (param_2 & 0x7f) << 1;
  } while (bVar1 < 8);
  return;
}

