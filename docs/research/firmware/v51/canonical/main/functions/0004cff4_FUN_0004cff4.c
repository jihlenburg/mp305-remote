/* Address: 0004cff4; name: FUN_0004cff4; body bytes: 200 */

void FUN_0004cff4(undefined4 param_1,int param_2,undefined4 *param_3,undefined4 param_4)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  
  *param_3 = param_1;
  param_3[1] = param_2;
  bVar1 = FUN_0004c924(param_1,param_2,0x4d,param_4,param_4);
  *(byte *)(param_3 + 0xf) = bVar1;
  if (2 < bVar1) {
    uVar2 = FUN_0004c774(param_1,param_2);
    if (uVar2 < 0xfd) {
      *(char *)(param_3 + 0xf) =
           (char)((uint)((int)(short)(ushort)*(byte *)(param_3 + 0xf) * (int)(short)uVar2) >> 8);
    }
    if (2 < *(byte *)(param_3 + 0xf)) {
      iVar3 = FUN_0004c924(param_1,param_2,0x48);
      param_3[0xc] = iVar3;
      if (iVar3 != 0) {
        uVar4 = FUN_0004c924(param_1,param_2,0x4c);
        uVar4 = FUN_0004eb66(param_1,param_2,uVar4);
        *(short *)(param_3 + 0xb) = (short)uVar4;
        *(char *)((int)param_3 + 0x2e) = (char)((uint)uVar4 >> 0x10);
        iVar3 = FUN_0004c924(param_1,param_2,0x49);
        param_3[0xd] = iVar3;
        if (iVar3 != 0) {
          uVar4 = FUN_0004c924(param_1,param_2,0x4a);
          param_3[0xe] = uVar4;
        }
        iVar3 = FUN_0004c924(param_1,param_2,0x4b);
        *(byte *)((int)param_3 + 0x3d) =
             *(byte *)((int)param_3 + 0x3d) & 0xf3 | (iVar3 != 0) << 2 | (iVar3 != 0) << 3;
        if (param_2 != 0) {
          bVar1 = FUN_0004c62c(param_1,param_2);
          *(byte *)((int)param_3 + 0x3d) = *(byte *)((int)param_3 + 0x3d) & 0xfc | bVar1 & 3;
        }
      }
    }
  }
  return;
}

