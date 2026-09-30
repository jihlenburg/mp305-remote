/* Address: 00016854; name: FUN_00016854; body bytes: 182 */

/* Recovered from stored Thumb pointer at 000634e8; callback identification is inferred until
   reviewed. */

void FUN_00016854(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00016932(&DAT_4004e000,1);
  if (iVar1 == 1) {
    FUN_00016830(&DAT_4004e000,0x1001);
    FUN_00016988(&DAT_4004e000,0x1010,1);
    if (DAT_1fff8ea0 == '\0') {
      FUN_00016988(&DAT_4004e000,8,1);
      uVar2 = 0;
    }
    else {
      if (DAT_1fff8eb0 == 1) {
        FUN_000166dc(&DAT_4004e000,0x400);
      }
      FUN_00016988(&DAT_4004e000,0x40,1);
      uVar2 = 1;
    }
    FUN_0001854c(0x15,uVar2);
  }
  iVar1 = FUN_00016932(&DAT_4004e000,0x1000);
  if (iVar1 == 1) {
    FUN_00016830(&DAT_4004e000,0x1000);
    FUN_00016988(&DAT_4004e000,0x10c8,0);
    FUN_00016928(&DAT_4004e000);
  }
  iVar1 = FUN_00016932(&DAT_4004e000,0x10);
  if (iVar1 == 1) {
    FUN_00016988(&DAT_4004e000,0x10d8,0);
    FUN_00016830(&DAT_4004e000,0x10);
    FUN_00016834(&DAT_4004e000,0);
    DAT_1fff8ec0 = 1;
  }
  return;
}

