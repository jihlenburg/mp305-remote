/* Address: 0004f990; name: FUN_0004f990; body bytes: 114 */

/* WARNING: Removing unreachable block (ram,0x0005ab34) */
/* WARNING: Removing unreachable block (ram,0x0005ab5a) */
/* WARNING: Removing unreachable block (ram,0x0005ab5c) */
/* Recovered from stored Thumb pointer at 0007ae24; callback identification is inferred until
   reviewed. */

void FUN_0004f990(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar1 = FUN_00046688(param_2);
  if ((iVar1 == 0x1a) || (iVar2 = FUN_0004b9b2(&DAT_0007ae18,param_2), iVar2 == 1)) {
    uVar3 = FUN_00046698(param_2);
    if (iVar1 == 0x18) {
      piVar4 = (int *)FUN_0004673a(param_2);
      FUN_0004bc8c(uVar3);
      iVar2 = FUN_00037b88();
      iVar5 = FUN_0004ccf8(uVar3);
      iVar1 = *piVar4;
      if (*piVar4 <= iVar2 - iVar5) {
        iVar1 = iVar2 - iVar5;
      }
      *piVar4 = iVar1;
    }
    else {
      if (iVar1 == 0x2e) {
        iVar1 = FUN_0004bc8c();
        iVar2 = FUN_0003759c();
        if (iVar2 == 0) {
          return;
        }
        uVar3 = FUN_000491e8();
        iVar5 = FUN_0004b108(iVar2,0,uVar3);
        iVar7 = 0;
        if (iVar5 != 1) {
          if (iVar5 == 2) {
            iVar5 = FUN_0004bb1a(iVar1,0);
            iVar7 = FUN_0004ccf8(iVar2);
            iVar7 = (iVar5 - iVar7) / 2;
          }
          else if (iVar5 == 3) {
            iVar7 = FUN_0004bb1a(iVar1,0);
            iVar5 = FUN_0004ccf8(iVar2);
            iVar7 = iVar7 - iVar5;
          }
        }
        FUN_0004eb0e(iVar2,iVar7);
        uVar3 = FUN_0004cb3a(iVar1,0);
        iVar5 = FUN_0004cb82(iVar1,0);
        iVar7 = FUN_00046bd6(uVar3);
        iVar6 = FUN_0004baf8(iVar1);
        FUN_0004c924(iVar1,0,100);
        FUN_0003a6ba(iVar1);
        iVar1 = *(int *)(iVar1 + 0x30);
        FUN_0003c97c(iVar2,0x5e7b9);
        FUN_0004eb3a(iVar2,(iVar6 / 2 - iVar7 / 2) - iVar1 * (iVar7 + iVar5));
        return;
      }
      if (iVar1 == 0x1a) {
        FUN_0002c7a8(param_2);
        return;
      }
    }
  }
  return;
}

