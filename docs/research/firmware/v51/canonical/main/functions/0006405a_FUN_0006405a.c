/* Address: 0006405a; name: FUN_0006405a; body bytes: 484 */

void FUN_0006405a(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7,int param_8,int param_9,int param_10,int param_11,int param_12,
                 int param_13)

{
  int iVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  undefined2 uVar6;
  ushort uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  undefined2 *puVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined1 uVar14;
  short sVar15;
  int iVar16;
  uint uVar17;
  uint uVar18;
  byte *pbVar19;
  uint uVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  
  iVar8 = param_4 * param_3 + param_1;
  iVar9 = param_4 / 2;
  iVar21 = 0;
  do {
    if (param_9 <= iVar21) {
      return;
    }
    uVar18 = param_5 + (iVar21 * param_7 >> 8);
    uVar10 = param_6 + (iVar21 * param_8 >> 8);
    iVar16 = (int)uVar18 >> 8;
    iVar1 = (int)uVar10 >> 8;
    if ((((iVar16 < 0) || (param_2 <= iVar16)) || (iVar1 < 0)) || (param_3 <= iVar1)) {
      uVar14 = 0;
LAB_00064226:
      *(undefined1 *)(param_11 + iVar21) = uVar14;
    }
    else {
      uVar18 = uVar18 & 0xff;
      uVar10 = uVar10 & 0xff;
      if (uVar18 < 0x80) {
        iVar22 = -1;
        uVar18 = (0x7f - uVar18) * 2;
      }
      else {
        iVar22 = 1;
        uVar18 = uVar18 * 2 - 0x100;
      }
      if (uVar10 < 0x80) {
        iVar23 = -1;
        uVar10 = (0x7f - uVar10) * 2;
      }
      else {
        iVar23 = 1;
        uVar10 = uVar10 * 2 - 0x100;
      }
      puVar11 = (undefined2 *)(iVar1 * param_4 + param_1 + iVar16 * 2);
      *(undefined2 *)(param_10 + iVar21 * 2) = *puVar11;
      sVar15 = (short)uVar18;
      sVar5 = (short)uVar10;
      if (((param_13 == 0) || (iVar16 + iVar22 < 0)) ||
         ((param_2 + -1 < iVar16 + iVar22 ||
          ((iVar1 + iVar23 < 0 || (param_3 + -1 < iVar1 + iVar23)))))) {
        if (param_12 == 0) {
          uVar7 = 0xff;
        }
        else {
          uVar7 = (ushort)*(byte *)(iVar1 * iVar9 + iVar8 + iVar16);
        }
        if ((((iVar16 == 0) && (iVar22 < 0)) ||
            (((iVar16 == param_2 + -1 && (0 < iVar22)) ||
             ((sVar15 = sVar5, iVar1 == 0 && (iVar23 < 0)))))) ||
           ((iVar1 == param_3 + -1 && (0 < iVar23)))) {
          uVar14 = (undefined1)((uint)((int)(short)(0xff - sVar15) * (int)(short)uVar7) >> 8);
          goto LAB_00064226;
        }
        *(char *)(param_11 + iVar21) = (char)uVar7;
      }
      else {
        sVar4 = puVar11[iVar22];
        sVar3 = *(short *)((int)puVar11 + iVar23 * param_4);
        if (param_12 == 0) {
          *(undefined1 *)(param_11 + iVar21) = 0xff;
        }
        else {
          pbVar19 = (byte *)(iVar1 * iVar9 + iVar8 + iVar16);
          bVar2 = *pbVar19;
          *(byte *)(param_11 + iVar21) = bVar2;
          uVar17 = (uint)pbVar19[iVar22];
          uVar20 = (uint)pbVar19[iVar23 * iVar9];
          if (bVar2 != uVar20) {
            uVar20 = ((int)(short)(ushort)pbVar19[iVar23 * iVar9] * (int)sVar5 +
                      (int)(short)(ushort)bVar2 * (int)(short)(0x100 - sVar5) & 0xffffU) >> 8;
          }
          if (bVar2 != uVar17) {
            uVar17 = ((int)(short)(ushort)pbVar19[iVar22] * (int)sVar15 +
                      (int)(short)(ushort)bVar2 * (int)(short)(0x100 - sVar15) & 0xffffU) >> 8;
          }
          uVar17 = uVar20 + uVar17 >> 1;
          *(char *)(param_11 + iVar21) = (char)uVar17;
          if (uVar17 == 0) goto LAB_00064230;
        }
        sVar5 = *(short *)(param_10 + iVar21 * 2);
        if ((sVar5 != sVar3) || (sVar5 != sVar4)) {
          uVar12 = FUN_0003ff4c(sVar3,sVar5,uVar10 & 0xff);
          uVar13 = FUN_0003ff4c(sVar4,*(undefined2 *)(param_10 + iVar21 * 2),uVar18 & 0xff);
          uVar6 = FUN_0003ff4c(uVar13,uVar12,0x7f);
          *(undefined2 *)(param_10 + iVar21 * 2) = uVar6;
        }
      }
    }
LAB_00064230:
    iVar21 = iVar21 + 1;
  } while( true );
}

