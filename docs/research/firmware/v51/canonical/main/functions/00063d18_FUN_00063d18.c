/* Address: 00063d18; name: FUN_00063d18; body bytes: 366 */

void FUN_00063d18(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7,int param_8,int param_9,int param_10,int param_11)

{
  int iVar1;
  byte bVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  short sVar6;
  short sVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  byte *pbVar11;
  int local_5c;
  int local_54;
  
  iVar4 = 0;
  do {
    if (param_9 <= iVar4) {
      return;
    }
    uVar10 = param_5 + (iVar4 * param_7 >> 8);
    uVar8 = param_6 + (iVar4 * param_8 >> 8);
    iVar5 = (int)uVar10 >> 8;
    iVar1 = (int)uVar8 >> 8;
    if ((((iVar5 < 0) || (param_2 <= iVar5)) || (iVar1 < 0)) || (param_3 <= iVar1)) {
      *(undefined4 *)(param_10 + iVar4 * 4) = 0;
    }
    else {
      uVar10 = uVar10 & 0xff;
      uVar8 = uVar8 & 0xff;
      sVar6 = (short)uVar10;
      if (uVar10 < 0x80) {
        local_5c = -1;
        sVar6 = (0x7f - sVar6) * 2;
      }
      else {
        local_5c = 1;
        sVar6 = sVar6 * 2 + -0x100;
      }
      sVar7 = (short)uVar8;
      if (uVar8 < 0x80) {
        local_54 = -1;
        sVar7 = (0x7f - sVar7) * 2;
      }
      else {
        local_54 = 1;
        sVar7 = sVar7 * 2 + -0x100;
      }
      pbVar11 = (byte *)(iVar1 * param_4 + param_1 + iVar5);
      iVar9 = param_10 + iVar4 * 4;
      bVar2 = *pbVar11;
      *(byte *)(param_10 + iVar4 * 4) = bVar2;
      *(byte *)(iVar9 + 1) = bVar2;
      *(byte *)(iVar9 + 2) = bVar2;
      *(undefined1 *)(iVar9 + 3) = 0xff;
      if (((param_11 == 0) || (iVar5 + local_5c < 0)) ||
         ((param_2 + -1 < iVar5 + local_5c ||
          ((iVar1 + local_54 < 0 || (param_3 + -1 < iVar1 + local_54)))))) {
        if (((iVar5 == 0) && (local_5c < 0)) || ((iVar5 == param_2 + -1 && (0 < local_5c)))) {
          bVar2 = *pbVar11;
          sVar7 = sVar6;
        }
        else {
          if (((iVar1 != 0) || (-1 < local_54)) && ((iVar1 != param_3 + -1 || (local_54 < 1))))
          goto LAB_00063e78;
          bVar2 = *pbVar11;
        }
        *(char *)(iVar9 + 3) =
             (char)((uint)((int)(short)(ushort)bVar2 * (int)(short)(0xff - sVar7)) >> 8);
      }
      else {
        uVar10 = (uint)pbVar11[local_5c];
        uVar8 = (uint)pbVar11[param_4 * local_54];
        bVar2 = *pbVar11;
        if (bVar2 != uVar10) {
          uVar10 = ((int)(short)(ushort)pbVar11[local_5c] * (int)sVar7 +
                    (int)(short)(ushort)bVar2 * (int)(short)(0x100 - sVar7) & 0xffffU) >> 8;
        }
        if (bVar2 != uVar8) {
          uVar8 = ((int)(short)(ushort)pbVar11[param_4 * local_54] * (int)sVar6 +
                   (int)(short)(ushort)bVar2 * (int)(short)(0x100 - sVar6) & 0xffffU) >> 8;
        }
        uVar3 = (undefined1)(uVar8 + uVar10 >> 1);
        *(undefined1 *)(param_10 + iVar4 * 4) = uVar3;
        *(undefined1 *)(iVar9 + 1) = uVar3;
        *(undefined1 *)(iVar9 + 2) = uVar3;
      }
    }
LAB_00063e78:
    iVar4 = iVar4 + 1;
  } while( true );
}

