/* Address: 00046894; name: FUN_00046894; body bytes: 402 */

int FUN_00046894(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  byte bVar6;
  uint uVar7;
  int iVar8;
  byte *pbVar9;
  uint *puVar10;
  int *piVar11;
  undefined1 uVar12;
  
  iVar8 = *(int *)(param_2 + 0x10);
  piVar11 = *(int **)(*param_1 + 0x18);
  iVar1 = 0;
  if (param_1[4] != 0) {
    puVar10 = (uint *)(piVar11[1] + param_1[4] * 8);
    if (((int)(short)(ushort)(byte)puVar10[1] * (int)(short)(ushort)*(byte *)((int)puVar10 + 5) == 0
        ) || (*(ushort *)((int)piVar11 + 0x12) >> 0xe != 0)) {
      iVar1 = 0;
    }
    else {
      pbVar9 = (byte *)(*piVar11 + (*puVar10 & 0xfffff));
      uVar7 = 0;
      iVar2 = FUN_00041788((byte)puVar10[1],0xe);
      uVar3 = (*(ushort *)((int)piVar11 + 0x12) & 0x1fff) >> 9;
      iVar1 = param_2;
      if (uVar3 == 1) {
        for (iVar5 = 0; iVar5 < (int)(uint)*(byte *)((int)puVar10 + 5); iVar5 = iVar5 + 1) {
          for (iVar4 = 0; iVar4 < (int)(uint)(byte)puVar10[1]; iVar4 = iVar4 + 1) {
            uVar7 = uVar7 & 7;
            if (uVar7 == 0) {
              bVar6 = *pbVar9;
LAB_00046948:
              *(char *)(iVar8 + iVar4) = (char)bVar6 >> 7;
            }
            else {
              if (uVar7 == 1) {
                bVar6 = (byte)(((uint)*pbVar9 << 0x19) >> 0x18);
                goto LAB_00046948;
              }
              if (uVar7 == 2) {
                bVar6 = (byte)(((uint)*pbVar9 << 0x1a) >> 0x18);
                goto LAB_00046948;
              }
              if (uVar7 == 3) {
                bVar6 = (byte)(((uint)*pbVar9 << 0x1b) >> 0x18);
                goto LAB_00046948;
              }
              if (uVar7 == 4) {
                bVar6 = (byte)(((uint)*pbVar9 << 0x1c) >> 0x18);
                goto LAB_00046948;
              }
              if (uVar7 == 5) {
                bVar6 = (byte)(((uint)*pbVar9 << 0x1d) >> 0x18);
                goto LAB_00046948;
              }
              if (uVar7 == 6) {
                bVar6 = (byte)(((uint)*pbVar9 << 0x1e) >> 0x18);
                goto LAB_00046948;
              }
              if (uVar7 == 7) {
                uVar12 = 0;
                if ((*pbVar9 & 1) != 0) {
                  uVar12 = 0xff;
                }
                *(undefined1 *)(iVar8 + iVar4) = uVar12;
                pbVar9 = pbVar9 + 1;
              }
            }
            uVar7 = uVar7 + 1;
          }
          iVar8 = iVar8 + iVar2;
        }
      }
      else if (uVar3 == 2) {
        for (iVar5 = 0; iVar5 < (int)(uint)*(byte *)((int)puVar10 + 5); iVar5 = iVar5 + 1) {
          for (iVar4 = 0; iVar4 < (int)(uint)(byte)puVar10[1]; iVar4 = iVar4 + 1) {
            uVar7 = uVar7 & 3;
            if (uVar7 == 0) {
              uVar12 = (&DAT_000671a4)[*pbVar9 >> 6];
LAB_000469be:
              *(undefined1 *)(iVar8 + iVar4) = uVar12;
            }
            else {
              if (uVar7 == 1) {
                uVar3 = (*pbVar9 & 0x3f) >> 4;
LAB_000469ba:
                uVar12 = (&DAT_000671a4)[uVar3];
                goto LAB_000469be;
              }
              if (uVar7 == 2) {
                uVar3 = (*pbVar9 & 0xf) >> 2;
                goto LAB_000469ba;
              }
              if (uVar7 == 3) {
                uVar3 = *pbVar9 & 3;
                pbVar9 = pbVar9 + 1;
                goto LAB_000469ba;
              }
            }
            uVar7 = uVar7 + 1;
          }
          iVar8 = iVar8 + iVar2;
        }
      }
      else if (uVar3 == 4) {
        for (iVar5 = 0; iVar5 < (int)(uint)*(byte *)((int)puVar10 + 5); iVar5 = iVar5 + 1) {
          for (iVar4 = 0; iVar4 < (int)(uint)(byte)puVar10[1]; iVar4 = iVar4 + 1) {
            uVar7 = uVar7 & 1;
            if (uVar7 == 0) {
              uVar12 = (&DAT_000671a8)[*pbVar9 >> 4];
LAB_000469fc:
              *(undefined1 *)(iVar8 + iVar4) = uVar12;
            }
            else if (uVar7 != 0) {
              uVar12 = (&DAT_000671a8)[*pbVar9 & 0xf];
              pbVar9 = pbVar9 + 1;
              goto LAB_000469fc;
            }
            uVar7 = uVar7 + 1;
          }
          iVar8 = iVar8 + iVar2;
        }
      }
    }
  }
  return iVar1;
}

