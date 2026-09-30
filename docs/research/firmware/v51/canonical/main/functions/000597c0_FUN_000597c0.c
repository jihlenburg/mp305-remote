/* Address: 000597c0; name: FUN_000597c0; body bytes: 88 */

/* Recovered from stored Thumb pointer at 000223b8; callback identification is inferred until
   reviewed. */

void FUN_000597c0(void)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  if (DAT_1ffe04f4 != 0) {
    DAT_1fffaaec = DAT_1fffaaec == '\0';
    uVar1 = FUN_00046756();
    uVar1 = FUN_0004b9de(uVar1,0);
    if (DAT_1fffaaec == '\0') {
      puVar2 = &DAT_0007ce38;
    }
    else {
      puVar2 = &DAT_0007e988;
    }
    FUN_00047d8e(uVar1,puVar2);
    if (DAT_1ffe02c0 != 0) {
      if (DAT_1fffaaec == '\0') {
        FUN_00052aae();
      }
      else {
        FUN_00052a74();
      }
    }
    FUN_0001cb8c(0xf);
    return;
  }
  return;
}

