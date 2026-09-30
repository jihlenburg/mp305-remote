/* Address: 0005ae30; name: FUN_0005ae30; body bytes: 340 */

undefined4 FUN_0005ae30(int param_1,int param_2,undefined4 param_3,uint param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  int local_30;
  int local_2c;
  undefined4 local_28;
  uint local_24;
  
  local_30 = param_1;
  local_2c = param_2;
  local_28 = param_3;
  local_24 = param_4;
  iVar2 = FUN_0003759c();
  if (iVar2 == 0) {
    uVar6 = 1;
  }
  else {
    iVar3 = FUN_00047eec();
    iVar4 = FUN_000482e0();
    if (((iVar4 == 4) || (iVar4 == 2)) &&
       (*(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_1 + 0x30), iVar4 == 4)) {
      uVar6 = FUN_0004bbe2(param_1);
      iVar4 = FUN_000472d4();
      if (iVar4 != 0) {
        FUN_0004743a(uVar6,0);
      }
    }
    iVar4 = FUN_000482e0(iVar3);
    if ((iVar4 == 1) || (iVar4 = FUN_000482e0(iVar3), iVar4 == 3)) {
      if ((int)((uint)*(byte *)(param_1 + 0x3c) << 0x1d) < 0) {
        uVar6 = FUN_0004cb3a(param_1,0);
        iVar7 = FUN_0004cb82(param_1,0);
        iVar8 = FUN_00046bd6(uVar6);
        iVar11 = *(int *)(param_1 + 0x20);
        iVar9 = *(int *)(param_1 + 0x18);
        local_30 = *(int *)(iVar3 + 0x60);
        local_2c = *(int *)(iVar3 + 100);
        FUN_000643e4(param_1,&local_30);
        iVar10 = 0;
        for (iVar4 = local_2c; iVar4 != 0;
            iVar4 = (int)((100 - (uint)*(byte *)(iVar3 + 0x25)) * iVar4) / 100) {
          iVar10 = iVar10 + iVar4;
        }
        iVar2 = ((iVar9 + (iVar11 - iVar9) / 2) - (*(int *)(iVar2 + 0x18) + iVar10)) /
                (iVar8 + iVar7);
        if (iVar2 < 0) {
          iVar2 = 0;
        }
        if (*(int *)(param_1 + 0x2c) <= iVar2) {
          iVar2 = *(int *)(param_1 + 0x2c) + -1;
        }
        iVar4 = (int)(short)iVar2;
      }
      else {
        iVar4 = 0;
        FUN_00048288(iVar3,&local_30);
        local_2c = local_2c - *(int *)(iVar2 + 0x18);
        local_30 = local_30 - *(int *)(iVar2 + 0x14);
        uVar5 = FUN_00048f08(iVar2,&local_30,1);
        uVar6 = FUN_000491e8(iVar2);
        local_24 = 0;
        for (uVar12 = 0; uVar1 = local_24, uVar12 < uVar5; uVar12 = uVar12 + 1) {
          iVar2 = FUN_00051cb0(uVar6,&local_24);
          if ((iVar2 == 10) && (uVar1 != uVar5)) {
            iVar4 = (int)(short)((short)iVar4 + 1);
          }
        }
      }
      if (-1 < iVar4) {
        FUN_0004fb30(param_1,iVar4,1);
      }
    }
    local_28 = *(undefined4 *)(param_1 + 0x30);
    uVar6 = FUN_0004e5a6(param_1,0x20,&local_28);
  }
  return uVar6;
}

