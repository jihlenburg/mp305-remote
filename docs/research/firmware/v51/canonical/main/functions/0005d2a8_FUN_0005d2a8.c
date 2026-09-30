/* Address: 0005d2a8; name: FUN_0005d2a8; body bytes: 64 */

/* Recovered from stored Thumb pointer at 00021ea0; callback identification is inferred until
   reviewed. */

void FUN_0005d2a8(void)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  DAT_1fffaadd = DAT_1fffaadd == '\0';
  uVar1 = FUN_0004b9de(DAT_1ffe0574,0);
  if (DAT_1fffaadd == '\0') {
    puVar2 = &DAT_0007e988;
  }
  else {
    puVar2 = &DAT_0007ce38;
  }
  FUN_00047d8e(uVar1,puVar2);
  if (DAT_1fffaadd != '\0') {
    FUN_00052aae();
    return;
  }
  FUN_00052a74(DAT_1ffe02a0);
  return;
}

