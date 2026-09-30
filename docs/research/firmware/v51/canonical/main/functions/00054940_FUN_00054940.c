/* Address: 00054940; name: FUN_00054940; body bytes: 108 */

void FUN_00054940(uint param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined *puVar3;
  
  if (DAT_1ffe0265 != param_1) {
    if (param_1 == 0) {
      FUN_00047d8e(DAT_1ffe070c,0);
      FUN_00049974(DAT_1ffe0710,&DAT_000549c8);
    }
    else {
      if (param_1 == 1) {
        puVar3 = &DAT_0007f128;
      }
      else {
        puVar3 = &DAT_0007f1c0;
      }
      FUN_00047d8e(DAT_1ffe070c,puVar3);
      FUN_00049974(DAT_1ffe0710,&DAT_1fffab24);
      FUN_0004e0e6(DAT_1ffe0708,0x80);
      uVar1 = FUN_0004037c(0xffffff);
      uVar2 = FUN_0004b9de(DAT_1ffe0708,0);
      FUN_0004e960(uVar2,uVar1,0);
    }
    DAT_1ffe0265 = (byte)param_1;
  }
  return;
}

