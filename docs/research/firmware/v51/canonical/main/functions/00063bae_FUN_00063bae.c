/* Address: 00063bae; name: FUN_00063bae; body bytes: 362 */

void FUN_00063bae(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7,int param_8,int param_9,int param_10,int param_11)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  short sVar6;
  uint uVar7;
  byte *pbVar8;
  int iVar9;
  uint uVar10;
  int local_5c;
  int local_50;
  
  iVar3 = 0;
  do {
    if (param_9 <= iVar3) {
      return;
    }
    uVar10 = param_5 + (iVar3 * param_7 >> 8);
    uVar7 = param_6 + (iVar3 * param_8 >> 8);
    iVar4 = (int)uVar10 >> 8;
    iVar1 = (int)uVar7 >> 8;
    if ((((iVar4 < 0) || (param_2 <= iVar4)) || (iVar1 < 0)) || (param_3 <= iVar1)) {
      *(undefined1 *)(param_10 + iVar3 * 2) = 0;
      *(undefined1 *)(param_10 + iVar3 * 2 + 1) = 0;
    }
    else {
      uVar10 = uVar10 & 0xff;
      uVar7 = uVar7 & 0xff;
      sVar5 = (short)uVar10;
      if (uVar10 < 0x80) {
        local_5c = -1;
        sVar5 = (0x7f - sVar5) * 2;
      }
      else {
        local_5c = 1;
        sVar5 = sVar5 * 2 + -0x100;
      }
      sVar6 = (short)uVar7;
      if (uVar7 < 0x80) {
        local_50 = -1;
        sVar6 = (0x7f - sVar6) * 2;
      }
      else {
        local_50 = 1;
        sVar6 = sVar6 * 2 + -0x100;
      }
      pbVar8 = (byte *)(iVar1 * param_4 + param_1 + iVar4);
      bVar2 = *pbVar8;
      *(byte *)(param_10 + iVar3 * 2) = bVar2;
      iVar9 = param_10 + iVar3 * 2;
      *(undefined1 *)(iVar9 + 1) = 0xff;
      if (((param_11 == 0) || (iVar4 + local_5c < 0)) ||
         ((param_2 + -1 < iVar4 + local_5c ||
          ((iVar1 + local_50 < 0 || (param_3 + -1 < iVar1 + local_50)))))) {
        if (((iVar4 == 0) && (local_5c < 0)) || ((iVar4 == param_2 + -1 && (0 < local_5c)))) {
          bVar2 = *pbVar8;
          sVar6 = sVar5;
        }
        else {
          if (((iVar1 != 0) || (-1 < local_50)) && ((iVar1 != param_3 + -1 || (local_50 < 1))))
          goto LAB_00063d0a;
          bVar2 = *pbVar8;
        }
        *(char *)(iVar9 + 1) =
             (char)((uint)((int)(short)(ushort)bVar2 * (int)(short)(0xff - sVar6)) >> 8);
      }
      else {
        uVar10 = (uint)pbVar8[local_5c];
        uVar7 = (uint)pbVar8[param_4 * local_50];
        if (bVar2 != uVar10) {
          uVar10 = ((int)(short)(ushort)pbVar8[local_5c] * (int)sVar6 +
                    (int)(short)(ushort)bVar2 * (int)(short)(0x100 - sVar6) & 0xffffU) >> 8;
        }
        if (bVar2 != uVar7) {
          uVar7 = ((int)(short)(ushort)pbVar8[param_4 * local_50] * (int)sVar5 +
                   (int)(short)(ushort)bVar2 * (int)(short)(0x100 - sVar5) & 0xffffU) >> 8;
        }
        *(char *)(param_10 + iVar3 * 2) = (char)(uVar7 + uVar10 >> 1);
      }
    }
LAB_00063d0a:
    iVar3 = iVar3 + 1;
  } while( true );
}

