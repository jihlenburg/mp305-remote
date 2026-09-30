/* Address: 00057314; name: FUN_00057314; body bytes: 52 */

void FUN_00057314(uint param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  if (DAT_1ffe034c == 0) {
    DAT_1ffe025a = 0xff;
  }
  else if (DAT_1ffe025a != param_1) {
    DAT_1ffe025a = (byte)param_1;
    uVar1 = FUN_0004b9de(DAT_1ffe03ac,3);
    if (param_1 == 0) {
      puVar2 = &DAT_0007cd08;
    }
    else {
      puVar2 = &DAT_0007cdc4;
    }
    FUN_00047d8e(uVar1,puVar2);
    return;
  }
  return;
}

