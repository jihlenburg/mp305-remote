/* Address: 000654c4; name: FUN_000654c4; body bytes: 416 */

void FUN_000654c4(int param_1,int *param_2,undefined4 param_3,uint param_4)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  int *local_30;
  uint local_28;
  
  piVar2 = (int *)(uint)*(ushort *)(param_1 + 0x28);
  if (piVar2 != param_2) {
    iVar3 = FUN_0004ed14(param_1,piVar2,param_2);
    if (iVar3 == 0) {
      *(short *)(param_1 + 0x28) = (short)param_2;
    }
    else {
      FUN_0004d3d8(param_1);
      *(short *)(param_1 + 0x28) = (short)param_2;
      FUN_0004ef6a(param_1);
      iVar4 = FUN_0004a360(0x280);
      uVar11 = 0;
      uVar5 = 0;
      local_30 = param_2;
      local_28 = param_4;
      while ((uVar5 < (*(ushort *)(param_1 + 0x2a) & 0x3ff) >> 4 && (uVar11 < 0x20))) {
        local_30 = (int *)(*(int *)(param_1 + 0xc) + uVar5 * 8);
        local_28 = *(uint *)(*(int *)(param_1 + 0xc) + uVar5 * 8 + 4);
        uVar12 = local_28 & 0xffff;
        local_28 = local_28 & 0xff0000;
        if (((uVar12 & ~(uint)param_2) == 0) && (-1 < local_30[1] << 6)) {
          piVar6 = (int *)*local_30;
          uVar10 = (uint)*(byte *)(piVar6 + 2);
          if (uVar10 == 0xff) {
            iVar8 = 0;
LAB_00065560:
            cVar1 = *(char *)(*piVar6 + iVar8 * 8);
            if (cVar1 != '\0') {
              if (cVar1 != 'f') goto LAB_0006555e;
              piVar6 = *(int **)(*piVar6 + iVar8 * 8 + 4);
LAB_00065578:
              iVar8 = 0;
              while ((*(char *)(*piVar6 + iVar8) != '\0' && (uVar11 < 0x20))) {
                for (uVar10 = 0; uVar10 < uVar11; uVar10 = uVar10 + 1) {
                  iVar9 = iVar4 + uVar10 * 0x14;
                  uVar7 = *(uint *)(iVar9 + 4);
                  if (((*(char *)(iVar9 + 8) == *(char *)(*piVar6 + iVar8)) &&
                      ((uVar7 & 0xff0000) == local_28)) && (uVar12 <= (uVar7 & 0xffff))) break;
                }
                if (uVar10 == uVar11) {
                  *(short *)(iVar4 + uVar11 * 0x14) = (short)piVar6[3];
                  iVar9 = iVar4 + uVar11 * 0x14;
                  *(short *)(iVar9 + 2) = (short)piVar6[4];
                  *(int *)(iVar9 + 0xc) = piVar6[2];
                  uVar11 = uVar11 + 1;
                  *(undefined1 *)(iVar9 + 8) = *(undefined1 *)(*piVar6 + iVar8);
                  *(int *)(iVar9 + 0x10) = piVar6[1];
                  *(uint *)(iVar9 + 4) = local_30[1] & 0xffffff;
                }
                iVar8 = iVar8 + 1;
              }
            }
            goto LAB_000655fa;
          }
          for (uVar7 = 0; uVar7 < uVar10; uVar7 = uVar7 + 1) {
            if (*(char *)(*piVar6 + uVar10 * 4 + uVar7) == 'f') {
              piVar6 = *(int **)(*piVar6 + uVar7 * 4);
              goto LAB_00065578;
            }
          }
        }
LAB_000655fa:
        uVar5 = uVar5 + 1;
      }
      for (uVar5 = 0; uVar5 < uVar11; uVar5 = uVar5 + 1) {
        local_30 = (int *)(iVar4 + uVar5 * 0x14);
        FUN_0004ebb0(param_1,local_30[1] & 0xff0000,piVar2,param_2);
      }
      FUN_00046bec(iVar4);
      if ((iVar3 == 1) || (iVar3 == 3)) {
        FUN_0004dedc(param_1,0xf0000,0xff);
        return;
      }
      if (iVar3 == 2) {
        FUN_0004d3d8(param_1);
        FUN_0004de6c(param_1,local_30,piVar2,local_28);
        return;
      }
    }
  }
  return;
LAB_0006555e:
  iVar8 = iVar8 + 1;
  goto LAB_00065560;
}

