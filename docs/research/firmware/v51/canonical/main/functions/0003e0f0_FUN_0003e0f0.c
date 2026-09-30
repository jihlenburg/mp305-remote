/* Address: 0003e0f0; name: FUN_0003e0f0; body bytes: 194 */

/* Recovered from stored Thumb pointer at 0007a5a4; callback identification is inferred until
   reviewed. */

void FUN_0003e0f0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar1 = FUN_0004b9b2(&PTR_DAT_0007a598);
  if (iVar1 == 1) {
    iVar1 = FUN_00046688(param_2);
    iVar2 = FUN_00046698(param_2);
    if (iVar1 == 0x18) {
      iVar1 = FUN_0004b03e(iVar2,0x20000);
      piVar3 = (int *)FUN_0004673a(param_2);
      if (iVar1 < *piVar3) {
        iVar1 = *piVar3;
      }
      *piVar3 = iVar1;
      iVar4 = FUN_0004c84c(iVar2,0);
      iVar1 = FUN_0004c894(iVar2,0);
      iVar5 = FUN_0004c8e8(iVar2,0);
      iVar6 = FUN_0004c7ec(iVar2,0);
      iVar2 = iVar1;
      if (iVar4 < iVar1) {
        iVar2 = iVar4;
      }
      iVar7 = iVar6;
      if (iVar5 < iVar6) {
        iVar7 = iVar5;
      }
      if (iVar2 < iVar7) {
        if (iVar4 < iVar1) {
          iVar1 = iVar4;
        }
      }
      else {
        iVar1 = iVar6;
        if (iVar5 < iVar6) {
          iVar1 = iVar5;
        }
      }
      if (iVar1 < 0) {
        *piVar3 = *piVar3 - iVar1;
      }
    }
    else {
      if ((iVar1 == 1) || (iVar1 == 8)) {
        FUN_0004d40e(iVar2,iVar2 + 0x3c);
        return;
      }
      if (iVar1 == 0x1a) {
        FUN_0002c234(param_2);
        return;
      }
    }
  }
  return;
}

