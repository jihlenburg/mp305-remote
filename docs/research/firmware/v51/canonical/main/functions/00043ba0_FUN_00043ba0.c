/* Address: 00043ba0; name: FUN_00043ba0; body bytes: 502 */

void FUN_00043ba0(undefined4 *param_1)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  ushort *puVar9;
  ushort *puVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  undefined1 *puVar14;
  bool bVar15;
  undefined4 local_34;
  int local_2c;
  
  iVar13 = param_1[1];
  iVar4 = param_1[2];
  iVar5 = FUN_00040568(param_1[6]);
  puVar14 = (undefined1 *)param_1[4];
  iVar6 = param_1[5];
  bVar1 = *(byte *)((int)param_1 + 0x1b);
  puVar9 = (ushort *)*param_1;
  iVar7 = param_1[3];
  uVar3 = (ushort)iVar5;
  if (puVar14 == (undefined1 *)0x0) {
    if (bVar1 < 0xfd) {
      local_2c = *puVar9 + 1;
      local_34 = 0;
      for (iVar6 = 0; iVar6 < iVar4; iVar6 = iVar6 + 1) {
        bVar15 = ((uint)puVar9 & 3) != 0;
        if (bVar15) {
          uVar3 = FUN_0003ff4c(iVar5,*puVar9,bVar1);
          *puVar9 = uVar3;
        }
        for (uVar11 = (uint)bVar15; (int)uVar11 < iVar13 + -2; uVar11 = uVar11 + 2) {
          puVar10 = puVar9 + uVar11;
          uVar3 = puVar9[uVar11];
          if (uVar3 == puVar10[1]) {
            if (*(int *)puVar10 == local_2c) {
              *(undefined4 *)puVar10 = local_34;
            }
            else {
              local_2c = *(int *)puVar10;
              uVar3 = FUN_0003ff4c(iVar5,uVar3,bVar1);
              puVar9[uVar11] = uVar3;
              puVar10[1] = uVar3;
              local_34 = *(undefined4 *)puVar10;
            }
          }
          else {
            uVar3 = FUN_0003ff4c(iVar5,uVar3,bVar1);
            puVar9[uVar11] = uVar3;
            uVar3 = FUN_0003ff4c(iVar5,puVar10[1],bVar1);
            puVar10[1] = uVar3;
          }
        }
        for (; (int)uVar11 < iVar13; uVar11 = uVar11 + 1) {
          uVar3 = FUN_0003ff4c(iVar5,puVar9[uVar11],bVar1);
          puVar9[uVar11] = uVar3;
        }
        puVar9 = (ushort *)((int)puVar9 + iVar7);
      }
    }
    else {
      for (iVar6 = 0; iVar6 < iVar4; iVar6 = iVar6 + 1) {
        puVar10 = puVar9;
        if (((uint)puVar9 & 3) != 0) {
          puVar10 = puVar9 + 1;
          *puVar9 = uVar3;
        }
        iVar8 = iVar5 * 0x10001;
        for (; puVar10 < puVar9 + (iVar13 - 1U & 0xfffffff0); puVar10 = puVar10 + 0x10) {
          *(int *)puVar10 = iVar8;
          *(int *)(puVar10 + 2) = iVar8;
          *(int *)(puVar10 + 4) = iVar8;
          *(int *)(puVar10 + 6) = iVar8;
          *(int *)(puVar10 + 8) = iVar8;
          *(int *)(puVar10 + 10) = iVar8;
          *(int *)(puVar10 + 0xc) = iVar8;
          *(int *)(puVar10 + 0xe) = iVar8;
        }
        for (; puVar10 < puVar9 + iVar13; puVar10 = puVar10 + 1) {
          *puVar10 = uVar3;
        }
        puVar9 = (ushort *)((int)puVar10 + iVar13 * -2 + iVar7);
      }
    }
  }
  else {
    iVar8 = 0;
    if (bVar1 < 0xfd) {
      for (; iVar8 < iVar4; iVar8 = iVar8 + 1) {
        for (iVar12 = 0; iVar12 < iVar13; iVar12 = iVar12 + 1) {
          uVar3 = FUN_0003ff4c(iVar5,puVar9[iVar12],
                               (uint)((int)(short)(ushort)(byte)puVar14[iVar12] *
                                     (int)(short)(ushort)bVar1) >> 8);
          puVar9[iVar12] = uVar3;
        }
        puVar9 = (ushort *)((int)puVar9 + iVar7);
        puVar14 = puVar14 + iVar6;
      }
    }
    else {
      for (; iVar8 < iVar4; iVar8 = iVar8 + 1) {
        bVar15 = ((uint)puVar14 & 1) != 0;
        if (bVar15) {
          uVar2 = FUN_0003ff4c(iVar5,*puVar9,*puVar14);
          *puVar9 = uVar2;
        }
        for (uVar11 = (uint)bVar15; (int)uVar11 <= iVar13 + -2; uVar11 = uVar11 + 2) {
          if (*(short *)(puVar14 + uVar11) == -1) {
            puVar9[uVar11] = uVar3;
            uVar2 = uVar3;
LAB_00043d2c:
            (puVar9 + uVar11)[1] = uVar2;
          }
          else if (*(short *)(puVar14 + uVar11) != 0) {
            uVar2 = FUN_0003ff4c(iVar5,puVar9[uVar11],puVar14[uVar11]);
            puVar9[uVar11] = uVar2;
            uVar2 = FUN_0003ff4c(iVar5,(puVar9 + uVar11)[1],puVar14[uVar11 + 1]);
            goto LAB_00043d2c;
          }
        }
        for (; (int)uVar11 < iVar13; uVar11 = uVar11 + 1) {
          uVar2 = FUN_0003ff4c(iVar5,puVar9[uVar11],puVar14[uVar11]);
          puVar9[uVar11] = uVar2;
        }
        puVar9 = (ushort *)((int)puVar9 + iVar7);
        puVar14 = puVar14 + iVar6;
      }
    }
  }
  return;
}

