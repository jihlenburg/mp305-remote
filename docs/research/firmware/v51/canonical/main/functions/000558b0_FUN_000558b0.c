/* Address: 000558b0; name: FUN_000558b0; body bytes: 132 */

void FUN_000558b0(uint param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  if (DAT_1ffe034c == 0) {
    DAT_1ffe0256 = 0xff;
  }
  else if (DAT_1ffe0256 != param_1) {
    uVar1 = FUN_0004b9de(DAT_1ffe0410,0);
    if (DAT_1fffaadc == '\0') {
      puVar2 = &DAT_0007bc48;
    }
    else {
      puVar2 = &DAT_0007cc4c;
    }
    FUN_00047d8e(uVar1,puVar2);
    uVar1 = FUN_0004b9de(DAT_1ffe0444,0);
    if (DAT_1fffaadc == '\0') {
      puVar2 = &DAT_0007bc48;
    }
    else {
      puVar2 = &DAT_0007cc4c;
    }
    FUN_00047d8e(uVar1,puVar2);
    uVar1 = FUN_0004b9de(DAT_1ffe0464,0);
    if (DAT_1fffaadc == '\0') {
      puVar2 = &DAT_0007bc48;
    }
    else {
      puVar2 = &DAT_0007cc4c;
    }
    FUN_00047d8e(uVar1,puVar2);
    DAT_1ffe0256 = (char)param_1;
    enter_critical();
    DAT_1fffaa35 = (char)param_1;
    exit_critical();
    return;
  }
  return;
}

