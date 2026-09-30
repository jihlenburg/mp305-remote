/* Address: 000270ec; name: FUN_000270ec; body bytes: 620 */

void FUN_000270ec(int *param_1,int param_2)

{
  char cVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint local_54;
  int local_50;
  int local_44 [4];
  uint local_34 [4];
  
  if (param_2 != 0) {
    param_1[6] = param_2;
    if (*param_1 != 0) {
      FUN_00046bec();
    }
    puVar2 = (undefined1 *)FUN_0004a318(param_2 * 6 + 6);
    *param_1 = (int)puVar2;
    if (puVar2 == (undefined1 *)0x0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    param_1[3] = (int)(puVar2 + param_2 * 2 + 2);
    param_1[1] = (int)puVar2;
    param_1[2] = (int)(puVar2 + param_2 * 4 + 4);
    if (param_2 == 1) {
      *puVar2 = 0xb4;
      *(undefined2 *)param_1[3] = 0;
      *(undefined2 *)(param_1[3] + 2) = 1;
      *(undefined2 *)param_1[2] = 0;
    }
    else {
      iVar3 = FUN_0004a360(param_2 * 0x10 + 0x10);
      iVar11 = 0;
      local_54 = param_2 * 4;
      local_50 = 0;
      iVar9 = param_2 * -4 + 1;
      local_44[0] = (int)local_54 >> 2;
      iVar10 = iVar3 + param_2 * 8 + 8;
      iVar7 = 0;
      local_34[0] = 0;
      while (iVar5 = FUN_0002735a(&local_54), iVar5 != 0) {
        iVar5 = 0;
        do {
          if (iVar9 < 1) {
            iVar4 = local_50 * 2 + 3;
          }
          else {
            iVar4 = (local_50 - local_54) * 2 + 5;
            local_54 = local_54 - 1;
          }
          iVar9 = iVar9 + iVar4;
          local_50 = local_50 + 1;
          iVar4 = FUN_0002735a(&local_54);
          if (iVar4 == 0) break;
          local_44[iVar5] = (int)local_54 >> 2;
          local_34[iVar5] = local_54 & 3;
          iVar5 = iVar5 + 1;
        } while (iVar5 < 4);
        if (iVar5 != 4) break;
        if (local_44[0] == local_44[3]) {
          *(int *)(iVar3 + iVar7 * 4) = local_44[0];
          *(int *)(iVar10 + iVar7 * 4) = iVar11;
          iVar5 = local_34[2] + local_34[3];
          uVar6 = local_34[0];
LAB_0002721c:
          iVar5 = iVar5 + local_34[1] + uVar6;
          iVar4 = param_1[1];
        }
        else {
          if (local_44[0] != local_44[1]) {
            *(int *)(iVar3 + iVar7 * 4) = local_44[0];
            *(int *)(iVar10 + iVar7 * 4) = iVar11;
            *(char *)(param_1[1] + iVar7) = (char)local_34[0];
            *(char *)(param_1[1] + iVar7) = (char)(local_34[0] << 4);
            iVar7 = iVar7 + 1;
            *(int *)(iVar3 + iVar7 * 4) = local_44[0] + -1;
            *(int *)(iVar10 + iVar7 * 4) = iVar11;
            iVar5 = local_34[3] + 4;
            uVar6 = local_34[2];
            goto LAB_0002721c;
          }
          *(int *)(iVar3 + iVar7 * 4) = local_44[0];
          *(int *)(iVar10 + iVar7 * 4) = iVar11;
          cVar1 = (char)local_34[0] + (char)local_34[1];
          if (local_44[0] == local_44[2]) {
            cVar1 = cVar1 + (char)local_34[2];
            *(char *)(param_1[1] + iVar7) = cVar1;
            *(char *)(param_1[1] + iVar7) = cVar1 * '\x10';
            iVar7 = iVar7 + 1;
            *(int *)(iVar3 + iVar7 * 4) = local_44[0] + -1;
            *(int *)(iVar10 + iVar7 * 4) = iVar11;
            iVar4 = param_1[1];
            iVar5 = local_34[3] + 0xc;
          }
          else {
            *(char *)(param_1[1] + iVar7) = cVar1;
            *(char *)(param_1[1] + iVar7) = cVar1 * '\x10';
            iVar7 = iVar7 + 1;
            *(int *)(iVar3 + iVar7 * 4) = local_44[0] + -1;
            *(int *)(iVar10 + iVar7 * 4) = iVar11;
            iVar5 = local_34[2] + local_34[3] + 8;
            iVar4 = param_1[1];
          }
        }
        iVar11 = iVar11 + 1;
        *(char *)(iVar4 + iVar7) = (char)iVar5;
        *(char *)(param_1[1] + iVar7) = (char)(iVar5 << 4);
        iVar7 = iVar7 + 1;
      }
      iVar9 = param_2 * 0x2d3 >> 10;
      if ((*(int *)(iVar3 + iVar7 * 4 + -4) != iVar9) ||
         (*(int *)(iVar10 + iVar7 * 4 + -4) != iVar9)) {
        iVar11 = param_2 * 0x2d3 + iVar9 * -0x400;
        if (iVar11 < 0x201) {
          iVar11 = iVar11 * iVar11 * 2 >> 0x10;
        }
        else {
          iVar11 = 0xf - ((0x400 - iVar11) * (0x400 - iVar11) * 2 >> 0x10);
        }
        *(int *)(iVar3 + iVar7 * 4) = iVar9;
        *(int *)(iVar10 + iVar7 * 4) = iVar9;
        *(char *)(param_1[1] + iVar7) = (char)iVar11;
        *(char *)(param_1[1] + iVar7) = (char)(iVar11 << 4);
        iVar7 = iVar7 + 1;
      }
      for (iVar9 = iVar7 + -2; -1 < iVar9; iVar9 = iVar9 + -1) {
        *(undefined4 *)(iVar3 + iVar7 * 4) = *(undefined4 *)(iVar10 + iVar9 * 4);
        *(undefined4 *)(iVar10 + iVar7 * 4) = *(undefined4 *)(iVar3 + iVar9 * 4);
        *(undefined1 *)(param_1[1] + iVar7) = *(undefined1 *)(param_1[1] + iVar9);
        iVar7 = iVar7 + 1;
      }
      iVar11 = 0;
      iVar9 = 0;
      *(undefined2 *)param_1[3] = 0;
      while (iVar9 < iVar7) {
        *(short *)(param_1[3] + iVar11 * 2) = (short)iVar9;
        *(undefined2 *)(param_1[2] + iVar11 * 2) = *(undefined2 *)(iVar3 + iVar9 * 4);
        for (; (*(int *)(iVar10 + iVar9 * 4) == iVar11 && (iVar9 < iVar7)); iVar9 = iVar9 + 1) {
          uVar6 = *(uint *)(iVar3 + iVar9 * 4);
          uVar8 = (uint)*(ushort *)(param_1[2] + iVar11 * 2);
          if ((int)uVar8 < (int)uVar6) {
            uVar6 = uVar8;
          }
          *(short *)(param_1[2] + iVar11 * 2) = (short)uVar6;
        }
        iVar11 = iVar11 + 1;
      }
      FUN_00046bec(iVar3);
    }
  }
  return;
}

