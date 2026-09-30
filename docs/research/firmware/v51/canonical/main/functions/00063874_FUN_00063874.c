/* Address: 00063874; name: FUN_00063874; body bytes: 356 */

void FUN_00063874(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7,int param_8,int param_9,int param_10,int param_11)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  undefined1 uVar5;
  short sVar6;
  short sVar7;
  uint uVar8;
  byte *pbVar9;
  uint uVar10;
  uint local_68;
  int local_60;
  int local_48;
  
  iVar3 = 0;
  do {
    if (param_9 <= iVar3) {
      return;
    }
    uVar10 = param_5 + (iVar3 * param_7 >> 8);
    uVar8 = param_6 + (param_8 * iVar3 >> 8);
    iVar4 = (int)uVar10 >> 8;
    iVar1 = (int)uVar8 >> 8;
    if ((((iVar4 < 0) || (param_2 <= iVar4)) || (iVar1 < 0)) || (param_3 <= iVar1)) {
      uVar5 = 0;
LAB_000639a0:
      *(undefined1 *)(param_10 + iVar3) = uVar5;
    }
    else {
      uVar10 = uVar10 & 0xff;
      uVar8 = uVar8 & 0xff;
      sVar6 = (short)uVar10;
      if (uVar10 < 0x80) {
        local_48 = -1;
        sVar6 = (0x7f - sVar6) * 2;
      }
      else {
        local_48 = 1;
        sVar6 = sVar6 * 2 + -0x100;
      }
      sVar7 = (short)uVar8;
      if (uVar8 < 0x80) {
        local_60 = -1;
        sVar7 = (0x7f - sVar7) * 2;
      }
      else {
        local_60 = 1;
        sVar7 = sVar7 * 2 + -0x100;
      }
      pbVar9 = (byte *)(iVar1 * param_4 + param_1 + iVar4);
      bVar2 = *pbVar9;
      *(byte *)(param_10 + iVar3) = bVar2;
      if (((param_11 != 0) && (-1 < iVar4 + local_48)) &&
         ((iVar4 + local_48 <= param_2 + -1 &&
          ((-1 < iVar1 + local_60 && (iVar1 + local_60 <= param_3 + -1)))))) {
        local_68 = (uint)pbVar9[local_48];
        uVar8 = (uint)pbVar9[param_4 * local_60];
        if (bVar2 != local_68) {
          local_68 = ((int)(short)(ushort)pbVar9[local_48] * (int)sVar7 +
                      (int)(short)(ushort)bVar2 * (int)(short)(0x100 - sVar7) & 0xffffU) >> 8;
        }
        if (bVar2 != uVar8) {
          uVar8 = ((int)(short)(ushort)pbVar9[param_4 * local_60] * (int)sVar6 +
                   (int)(short)(ushort)bVar2 * (int)(short)(0x100 - sVar6) & 0xffffU) >> 8;
        }
        uVar5 = (undefined1)(local_68 + uVar8 >> 1);
        goto LAB_000639a0;
      }
      if (((iVar4 == 0) && (local_48 < 0)) || ((iVar4 == param_2 + -1 && (0 < local_48)))) {
        bVar2 = *pbVar9;
        sVar7 = sVar6;
LAB_000639be:
        uVar5 = (undefined1)((uint)((int)(short)(ushort)bVar2 * (int)(short)(0xff - sVar7)) >> 8);
        goto LAB_000639a0;
      }
      if (((iVar1 == 0) && (local_60 < 0)) || ((iVar1 == param_3 + -1 && (0 < local_60)))) {
        bVar2 = *pbVar9;
        goto LAB_000639be;
      }
    }
    iVar3 = iVar3 + 1;
  } while( true );
}

