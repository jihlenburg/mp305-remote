/* Address: 000510ac; name: FUN_000510ac; body bytes: 214 */

/* Recovered from stored Thumb pointer at 0007aed8; callback identification is inferred until
   reviewed. */

void FUN_000510ac(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  
  iVar1 = FUN_0004b9b2(&PTR_DAT_0007aecc);
  if (iVar1 == 1) {
    iVar1 = FUN_00046688(param_2);
    uVar2 = FUN_00046698(param_2);
    if (iVar1 == 0x18) {
      iVar3 = FUN_0004c870(uVar2,0x30000);
      iVar1 = FUN_0004c8b2(uVar2,0x30000);
      iVar4 = FUN_0004c90c(uVar2,0x30000);
      iVar5 = FUN_0004c80a(uVar2,0x30000);
      iVar6 = iVar1;
      if (iVar1 < iVar3) {
        iVar6 = iVar3;
      }
      iVar8 = iVar4;
      if (iVar4 < iVar5) {
        iVar8 = iVar5;
      }
      if (iVar8 < iVar6) {
        if (iVar1 < iVar3) {
          iVar1 = iVar3;
        }
      }
      else {
        iVar1 = iVar5;
        if (iVar5 <= iVar4) {
          iVar1 = iVar4;
        }
      }
      iVar6 = FUN_0004b03e(uVar2,0x30000);
      iVar6 = iVar6 + iVar1 + 2;
      piVar7 = (int *)FUN_0004673a(param_2);
      if (iVar6 < *piVar7) {
        iVar6 = *piVar7;
      }
      *piVar7 = iVar6;
      iVar1 = FUN_0004b03e(uVar2,0x20000);
      iVar6 = *piVar7;
      if (iVar6 <= iVar1) {
        iVar6 = FUN_0004b03e(uVar2,0x20000);
      }
      *piVar7 = iVar6;
    }
    else {
      if (iVar1 == 0x20) {
        FUN_00051188();
        FUN_0004d3d8(uVar2);
        return;
      }
      if (iVar1 == 0x1a) {
        FUN_0002dc02(param_2);
        return;
      }
    }
  }
  return;
}

