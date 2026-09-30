/* Address: 0004d0bc; name: FUN_0004d0bc; body bytes: 794 */

void FUN_0004d0bc(undefined4 param_1,int param_2,undefined4 *param_3)

{
  short sVar1;
  byte bVar2;
  undefined1 uVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  undefined2 local_18;
  undefined1 uStack_16;
  
  *param_3 = param_1;
  param_3[1] = param_2;
  uVar4 = FUN_0004c774();
  if ((param_2 == 0) || (2 < uVar4)) {
    uVar5 = FUN_0004c924(param_1,param_2,0xc);
    param_3[7] = uVar5;
    if (*(char *)(param_3 + 8) != '\0') {
      bVar2 = FUN_0004c924(param_1,param_2,0x1d);
      *(byte *)(param_3 + 8) = bVar2;
      if (2 < bVar2) {
        uVar5 = FUN_0004c606(param_1,param_2);
        local_18 = (undefined2)uVar5;
        *(undefined2 *)((int)param_3 + 0x21) = local_18;
        uStack_16 = (undefined1)((uint)uVar5 >> 0x10);
        *(undefined1 *)((int)param_3 + 0x23) = uStack_16;
        iVar6 = FUN_0004c924(param_1,param_2,0x26);
        if ((iVar6 == 0) || ((*(byte *)(iVar6 + 0xb) & 7) == 0)) {
          bVar2 = FUN_0004c924(param_1,param_2,0x20);
          *(byte *)((int)param_3 + 0x2f) = *(byte *)((int)param_3 + 0x2f) & 0xf8 | bVar2 & 7;
          if ((bVar2 & 7) != 0) {
            uVar5 = FUN_0004c606(param_1,param_2);
            local_18 = (undefined2)uVar5;
            *(undefined2 *)(param_3 + 9) = local_18;
            uStack_16 = (undefined1)((uint)uVar5 >> 0x10);
            *(undefined1 *)((int)param_3 + 0x26) = uStack_16;
            uVar5 = FUN_0004c924(param_1,param_2,0x23);
            uVar5 = FUN_0004eb66(param_1,param_2,uVar5);
            local_18 = (undefined2)uVar5;
            *(undefined2 *)((int)param_3 + 0x29) = local_18;
            uStack_16 = (undefined1)((uint)uVar5 >> 0x10);
            *(undefined1 *)((int)param_3 + 0x2b) = uStack_16;
            uVar3 = FUN_0004c924(param_1,param_2,0x21);
            *(undefined1 *)(param_3 + 10) = uVar3;
            uVar3 = FUN_0004c924(param_1,param_2,0x22);
            *(undefined1 *)((int)param_3 + 0x2d) = uVar3;
            uVar3 = FUN_0004c924(param_1,param_2,0x24);
            *(undefined1 *)((int)param_3 + 0x27) = uVar3;
            uVar3 = FUN_0004c924(param_1,param_2,0x25);
            *(undefined1 *)(param_3 + 0xb) = uVar3;
          }
        }
        else {
          FUN_0004a404(param_3 + 9,iVar6,0xc);
        }
      }
    }
    if (*(char *)(param_3 + 0x12) != '\0') {
      iVar6 = FUN_0004c924(param_1,param_2,0x30);
      param_3[0x11] = iVar6;
      if (iVar6 != 0) {
        bVar2 = FUN_0004c924(param_1,param_2,0x32);
        *(byte *)(param_3 + 0x12) = bVar2;
        if (2 < bVar2) {
          bVar2 = FUN_0004c924(param_1,param_2,0x34);
          *(byte *)((int)param_3 + 0x49) = *(byte *)((int)param_3 + 0x49) & 0xe0 | bVar2 & 0x1f;
          uVar5 = FUN_0004c924(param_1,param_2,0x31);
          uVar5 = FUN_0004eb66(param_1,param_2,uVar5);
          local_18 = (undefined2)uVar5;
          *(undefined2 *)((int)param_3 + 0x3e) = local_18;
          uStack_16 = (undefined1)((uint)uVar5 >> 0x10);
          *(undefined1 *)(param_3 + 0x10) = uStack_16;
        }
      }
    }
    if (*(char *)(param_3 + 0x16) != '\0') {
      iVar6 = FUN_0004c7da(param_1,param_2);
      param_3[0x14] = iVar6;
      if (iVar6 != 0) {
        uVar7 = FUN_0004c7c8(param_1,param_2);
        *(char *)(param_3 + 0x16) = (char)uVar7;
        if (2 < uVar7) {
          uVar5 = FUN_0004c7d4(param_1,param_2);
          param_3[0x15] = uVar5;
          uVar5 = FUN_0004c924(param_1,param_2,0x39);
          uVar5 = FUN_0004eb66(param_1,param_2,uVar5);
          local_18 = (undefined2)uVar5;
          *(undefined2 *)((int)param_3 + 0x4a) = local_18;
          uStack_16 = (undefined1)((uint)uVar5 >> 0x10);
          *(undefined1 *)(param_3 + 0x13) = uStack_16;
        }
      }
    }
    if (*(char *)((int)param_3 + 0x3b) != '\0') {
      iVar6 = FUN_0004c924(param_1,param_2,0x28);
      param_3[0xc] = iVar6;
      if (iVar6 != 0) {
        bVar2 = FUN_0004c924(param_1,param_2,0x29);
        *(byte *)((int)param_3 + 0x3b) = bVar2;
        if (2 < bVar2) {
          iVar6 = FUN_00047ecc(param_3[0xc]);
          if (iVar6 == 2) {
            uVar5 = FUN_0004cb22(param_1,param_2);
            param_3[0xd] = uVar5;
            uVar5 = FUN_0004cb08(param_1,param_2);
            local_18 = (undefined2)uVar5;
            *(undefined2 *)(param_3 + 0xe) = local_18;
            uStack_16 = (undefined1)((uint)uVar5 >> 0x10);
            *(undefined1 *)((int)param_3 + 0x3a) = uStack_16;
          }
          else {
            uVar5 = FUN_0004c924(param_1,param_2,0x2a);
            uVar5 = FUN_0004eb66(param_1,param_2,uVar5);
            local_18 = (undefined2)uVar5;
            *(undefined2 *)(param_3 + 0xe) = local_18;
            uStack_16 = (undefined1)((uint)uVar5 >> 0x10);
            *(undefined1 *)((int)param_3 + 0x3a) = uStack_16;
            uVar3 = FUN_0004c924(param_1,param_2,0x2b);
            *(undefined1 *)(param_3 + 0xf) = uVar3;
            iVar6 = FUN_0004c924(param_1,param_2,0x2c);
            *(bool *)((int)param_3 + 0x3d) = iVar6 != 0;
          }
        }
      }
    }
    if (*(char *)(param_3 + 0x1b) != '\0') {
      iVar6 = FUN_0004c984(param_1,param_2);
      param_3[0x17] = iVar6;
      if ((iVar6 != 0) && (2 < *(byte *)(param_3 + 0x1b))) {
        uVar7 = FUN_0004c972(param_1,param_2);
        *(char *)(param_3 + 0x1b) = (char)uVar7;
        if (2 < uVar7) {
          uVar5 = FUN_0004c95a(param_1,param_2);
          param_3[0x18] = uVar5;
          uVar5 = FUN_0004c966(param_1,param_2);
          param_3[0x19] = uVar5;
          uVar5 = FUN_0004c97e(param_1,param_2);
          param_3[0x1a] = uVar5;
          uVar5 = FUN_0004c924(param_1,param_2,0x3d);
          uVar5 = FUN_0004eb66(param_1,param_2,uVar5);
          local_18 = (undefined2)uVar5;
          *(undefined2 *)((int)param_3 + 0x59) = local_18;
          uStack_16 = (undefined1)((uint)uVar5 >> 0x10);
          *(undefined1 *)((int)param_3 + 0x5b) = uStack_16;
        }
      }
    }
    if (uVar4 < 0xfd) {
      sVar1 = (short)uVar4;
      *(byte *)(param_3 + 8) =
           (byte)((uint)((int)(short)(ushort)*(byte *)(param_3 + 8) * (int)sVar1) >> 8);
      *(char *)((int)param_3 + 0x3b) =
           (char)((uint)((int)(short)(ushort)*(byte *)((int)param_3 + 0x3b) * (int)sVar1) >> 8);
      *(char *)(param_3 + 0x12) =
           (char)((uint)((int)(short)(ushort)*(byte *)(param_3 + 0x12) * (int)sVar1) >> 8);
      *(char *)(param_3 + 0x1b) =
           (char)((uint)((int)(short)(ushort)*(byte *)(param_3 + 0x1b) * (int)sVar1) >> 8);
      *(char *)(param_3 + 0x16) =
           (char)((uint)((int)(short)(ushort)*(byte *)(param_3 + 0x16) * (int)sVar1) >> 8);
      return;
    }
  }
  else {
    *(undefined1 *)(param_3 + 8) = 0;
    *(undefined1 *)((int)param_3 + 0x3b) = 0;
    *(undefined1 *)(param_3 + 0x12) = 0;
    *(undefined1 *)(param_3 + 0x16) = 0;
    *(undefined1 *)(param_3 + 0x1b) = 0;
  }
  return;
}

