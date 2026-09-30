/* Address: 0002756c; name: FUN_0002756c; body bytes: 90 */

/* Recovered from stored Thumb pointer at 00021ea8; callback identification is inferred until
   reviewed. */

void FUN_0002756c(void)

{
  undefined4 uVar1;
  int iVar2;
  
  DAT_1ffe0244 = 0;
  DAT_1fffaad3 = 0;
  FUN_0001814c();
  uVar1 = FUN_00037604();
  FUN_0004eb0e(DAT_1ffe05a8,uVar1);
  if (DAT_1ffe0330 != 0) {
    FUN_0001ba58();
    return;
  }
  if (DAT_1ffe04f4 == 0) {
    FUN_00018114(DAT_1ffe0348);
  }
  else {
    iVar2 = FUN_0004cd1e();
    if ((iVar2 == 0) && (iVar2 = FUN_0004cd1e(DAT_1ffe0540), iVar2 != 0)) {
      FUN_00017cf8();
    }
  }
  FUN_0001cb8c(0xf);
  return;
}

