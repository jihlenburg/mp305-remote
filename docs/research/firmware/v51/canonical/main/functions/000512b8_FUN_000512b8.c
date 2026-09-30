/* Address: 000512b8; name: FUN_000512b8; body bytes: 624 */

void FUN_000512b8(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  int iVar13;
  undefined4 extraout_r1;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  undefined8 uVar18;
  int local_20;
  int local_1c;
  
  local_20 = param_3;
  local_1c = param_4;
  iVar1 = FUN_0004b9b2(&PTR_DAT_0007aef0);
  if (iVar1 == 1) {
    iVar1 = FUN_00046688(param_2);
    uVar18 = FUN_00046698(param_2);
    uVar6 = (undefined4)((ulonglong)uVar18 >> 0x20);
    iVar2 = (int)uVar18;
    if (iVar1 == 0x2f) {
      uVar6 = FUN_0004c876(iVar2,&LAB_00050000,local_20,local_1c);
      uVar7 = FUN_0004c8b8(iVar2,&LAB_00050000);
      uVar8 = FUN_0004c912(iVar2,&LAB_00050000);
      uVar9 = FUN_0004c810(iVar2,&LAB_00050000);
      uVar10 = FUN_0004cb6a(iVar2,&LAB_00050000);
      uVar11 = FUN_0004cb88(iVar2,&LAB_00050000);
      uVar12 = FUN_0004cb46(iVar2,&LAB_00050000);
      iVar1 = FUN_0004c762(iVar2,&LAB_00050000);
      iVar13 = FUN_0004c756(iVar2,&LAB_00050000);
      for (uVar3 = 0; uVar3 < *(uint *)(iVar2 + 0x30); uVar3 = uVar3 + 1) {
        iVar14 = FUN_00037a1e(iVar2,uVar3,uVar12,uVar10,uVar11,uVar6,uVar7,uVar8,uVar9);
        iVar17 = iVar13;
        if (iVar14 < iVar13) {
          iVar17 = iVar14;
        }
        iVar16 = iVar1;
        if ((iVar1 <= iVar17) && (iVar16 = iVar14, iVar13 <= iVar14)) {
          iVar16 = iVar13;
        }
        *(int *)(*(int *)(iVar2 + 0x38) + uVar3 * 4) = iVar16;
      }
      FUN_0004deac(iVar2);
      FUN_0004d3d8(iVar2);
      return;
    }
    if (iVar1 == 0x31) {
      piVar4 = (int *)FUN_0004673a(param_2);
      iVar1 = 0;
      for (uVar3 = 0; uVar3 < *(uint *)(iVar2 + 0x2c); uVar3 = uVar3 + 1) {
        iVar1 = iVar1 + *(int *)(*(int *)(iVar2 + 0x3c) + uVar3 * 4);
      }
      iVar13 = 0;
      for (uVar3 = 0; uVar3 < *(uint *)(iVar2 + 0x30); uVar3 = uVar3 + 1) {
        iVar13 = iVar13 + *(int *)(*(int *)(iVar2 + 0x38) + uVar3 * 4);
      }
      *piVar4 = iVar1 + -1;
      piVar4[1] = iVar13 + -1;
    }
    else if ((iVar1 == 1) || (iVar1 == 2)) {
      iVar1 = FUN_000377fa(iVar2,&local_20,&local_1c);
      if ((iVar1 == 1) &&
         ((*(int *)(iVar2 + 0x40) != local_1c || (*(int *)(iVar2 + 0x44) != local_20)))) {
        *(int *)(iVar2 + 0x40) = local_1c;
        *(int *)(iVar2 + 0x44) = local_20;
        FUN_0004d3d8(iVar2);
      }
    }
    else if (iVar1 == 8) {
      FUN_0004d3d8();
      FUN_00047eec();
      iVar1 = FUN_000482c2();
      if ((((*(int *)(iVar2 + 0x40) == 0xffff) || (*(int *)(iVar2 + 0x44) == 0xffff)) ||
          (iVar1 != 0)) || (iVar1 = FUN_0004e5a6(iVar2,0x20,0), iVar1 == 1)) {
        FUN_00047eec();
        iVar1 = FUN_000482e0();
        if ((iVar1 == 1) || (iVar1 == 3)) {
          *(undefined4 *)(iVar2 + 0x40) = 0xffff;
          *(undefined4 *)(iVar2 + 0x44) = 0xffff;
        }
      }
    }
    else {
      if (iVar1 == 0x10) {
LAB_000513b8:
        FUN_0004d3d8(iVar2,uVar6,local_20,local_1c);
        return;
      }
      if (iVar1 == 0xe) {
        piVar4 = (int *)FUN_0004673a(param_2);
        iVar17 = *piVar4;
        iVar13 = *(int *)(iVar2 + 0x40);
        iVar1 = *(int *)(iVar2 + 0x44);
        if ((iVar13 == 0xffff) || (iVar1 == 0xffff)) {
          *(undefined4 *)(iVar2 + 0x40) = 0;
          *(undefined4 *)(iVar2 + 0x44) = 0;
          FUN_0005e538(iVar2);
          uVar6 = extraout_r1;
          goto LAB_000513b8;
        }
        iVar16 = *(int *)(iVar2 + 0x2c);
        iVar14 = iVar13;
        if (iVar16 <= iVar13) {
          iVar14 = 0;
        }
        iVar15 = *(int *)(iVar2 + 0x30);
        iVar5 = iVar1;
        if (iVar15 <= iVar1) {
          iVar5 = 0;
        }
        if (iVar17 == 0x14) {
          iVar14 = iVar14 + -1;
        }
        else if (iVar17 == 0x13) {
          iVar14 = iVar14 + 1;
        }
        else if (iVar17 == 0x11) {
          iVar5 = iVar5 + -1;
        }
        else {
          if (iVar17 != 0x12) {
            return;
          }
          iVar5 = iVar5 + 1;
        }
        if (iVar14 < iVar16) {
          if (iVar14 < 0) {
            if (iVar5 == 0) {
              iVar14 = 0;
            }
            else {
              iVar14 = iVar16 + -1;
              iVar5 = iVar5 + -1;
            }
          }
        }
        else if (iVar5 < iVar15 + -1) {
          iVar14 = 0;
          iVar5 = iVar5 + 1;
        }
        else {
          iVar14 = iVar16 + -1;
        }
        if (iVar5 < iVar15) {
          if (iVar5 < 0) {
            iVar5 = 0;
          }
        }
        else {
          iVar5 = iVar15 + -1;
        }
        if ((iVar13 != iVar14) || (iVar1 != iVar5)) {
          *(int *)(iVar2 + 0x40) = iVar14;
          *(int *)(iVar2 + 0x44) = iVar5;
          FUN_0004d3d8(iVar2);
          FUN_0005e538(iVar2);
          FUN_0004e5a6(iVar2,0x20,0);
          return;
        }
      }
      else if (iVar1 == 0x1a) {
        FUN_0002dd0e(param_2,uVar6,local_20,local_1c);
        return;
      }
    }
  }
  return;
}

