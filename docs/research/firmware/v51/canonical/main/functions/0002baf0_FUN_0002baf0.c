/* Address: 0002baf0; name: FUN_0002baf0; body bytes: 518 */

void FUN_0002baf0(int param_1,int param_2)

{
  short sVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  uint in_fpscr;
  float fVar13;
  undefined1 auStack_b0 [8];
  int local_a8;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  int local_70;
  int local_6c;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  int local_40;
  int local_2c;
  
  iVar4 = FUN_0003db4c(&local_50,param_1 + 0x14,param_2 + 0x18);
  if (iVar4 != 0) {
    local_68 = *(undefined4 *)(param_2 + 0x18);
    uStack_64 = *(undefined4 *)(param_2 + 0x1c);
    uStack_60 = *(undefined4 *)(param_2 + 0x20);
    uStack_5c = *(undefined4 *)(param_2 + 0x24);
    *(undefined4 *)(param_2 + 0x18) = local_50;
    *(undefined4 *)(param_2 + 0x1c) = uStack_4c;
    *(undefined4 *)(param_2 + 0x20) = uStack_48;
    *(undefined4 *)(param_2 + 0x24) = uStack_44;
    iVar4 = FUN_0004c696(param_1,0);
    local_40 = FUN_0004c858(param_1,0);
    local_40 = local_40 + iVar4;
    iVar5 = FUN_0004c8f4(param_1,0);
    local_6c = FUN_0004bb1a(param_1);
    local_70 = FUN_0004baf8(param_1);
    FUN_00042462(auStack_b0);
    FUN_0004cff4(param_1,0,auStack_b0);
    bVar2 = FUN_0004c924(param_1,0,0x32);
    iVar6 = FUN_0004c696(param_1,0);
    bVar3 = FUN_0004c924(param_1,0,0x34);
    uVar11 = (uint)bVar3;
    local_2c = FUN_0004bd90(param_1);
    iVar7 = FUN_0004bf14(param_1);
    if (*(int *)(param_1 + 0x68) != 0) {
      iVar9 = *(int *)(param_1 + 0x18);
      local_94 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x14),
                                            (byte)(in_fpscr >> 0x16) & 3);
      iVar10 = 0;
      local_8c = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x1c),
                                            (byte)(in_fpscr >> 0x16) & 3);
      sVar1 = *(short *)(param_1 + 0x68);
      iVar12 = (int)sVar1;
      if ((2 < bVar2) && (0 < iVar6)) {
        if (((int)(uVar11 << 0x1e) < 0) && (iVar8 = FUN_0004c8f4(param_1,0), iVar8 == 0)) {
          iVar10 = 1;
        }
        if (((bVar3 & 1) != 0) && (iVar8 = FUN_0004c924(param_1,0,0x11), iVar8 == 0)) {
          iVar12 = (int)(short)(sVar1 + -1);
        }
      }
      for (; iVar10 < iVar12; iVar10 = (int)(short)((short)iVar10 + 1)) {
        local_90 = (float)VectorUnsignedToFloat
                                    ((uint)(iVar10 * local_70) / (*(int *)(param_1 + 0x68) - 1U),
                                     (byte)(in_fpscr >> 0x16) & 3);
        fVar13 = (float)VectorSignedToFloat((iVar9 + iVar4 + iVar5) - iVar7,
                                            (byte)(in_fpscr >> 0x16) & 3);
        local_90 = local_90 + fVar13;
        local_a8 = iVar10;
        local_88 = local_90;
        FUN_000423a0(param_2,auStack_b0);
      }
    }
    if (*(int *)(param_1 + 0x6c) != 0) {
      local_90 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x18),
                                            (byte)(in_fpscr >> 0x16) & 3);
      iVar7 = (*(int *)(param_1 + 0x14) + local_40) - local_2c;
      iVar5 = 0;
      local_88 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x20),
                                            (byte)(in_fpscr >> 0x16) & 3);
      sVar1 = *(short *)(param_1 + 0x6c);
      iVar4 = (int)sVar1;
      if ((2 < bVar2) && (0 < iVar6)) {
        if (((int)(uVar11 << 0x1d) < 0) && (iVar6 = FUN_0004c858(param_1,0), iVar6 == 0)) {
          iVar5 = 1;
        }
        if (((int)(uVar11 << 0x1c) < 0) && (iVar6 = FUN_0004c924(param_1,0,0x13), iVar6 == 0)) {
          iVar4 = (int)(short)(sVar1 + -1);
        }
      }
      for (; iVar5 < iVar4; iVar5 = (int)(short)((short)iVar5 + 1)) {
        local_94 = (float)VectorUnsignedToFloat
                                    ((uint)(iVar5 * local_6c) / (*(int *)(param_1 + 0x6c) - 1U),
                                     (byte)(in_fpscr >> 0x16) & 3);
        fVar13 = (float)VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
        local_94 = local_94 + fVar13;
        local_a8 = iVar5;
        local_8c = local_94;
        FUN_000423a0(param_2,auStack_b0);
      }
    }
    *(undefined4 *)(param_2 + 0x18) = local_68;
    *(undefined4 *)(param_2 + 0x1c) = uStack_64;
    *(undefined4 *)(param_2 + 0x20) = uStack_60;
    *(undefined4 *)(param_2 + 0x24) = uStack_5c;
  }
  return;
}

