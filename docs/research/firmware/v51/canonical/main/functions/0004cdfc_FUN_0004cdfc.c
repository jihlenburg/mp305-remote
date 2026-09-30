/* Address: 0004cdfc; name: FUN_0004cdfc; body bytes: 144 */

void FUN_0004cdfc(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  
  *param_3 = param_1;
  param_3[1] = param_2;
  iVar2 = FUN_0004c924(param_1,param_2,0x50,param_4,param_4);
  param_3[8] = iVar2;
  if (iVar2 != 0) {
    bVar1 = FUN_0004c924(param_1,param_2,0x53);
    *(byte *)(param_3 + 0xf) = bVar1;
    if (2 < bVar1) {
      uVar3 = FUN_0004c774(param_1,param_2);
      if (uVar3 < 0xfd) {
        *(char *)(param_3 + 0xf) =
             (char)((uint)((int)(short)(ushort)*(byte *)(param_3 + 0xf) * (int)(short)uVar3) >> 8);
      }
      if (2 < *(byte *)(param_3 + 0xf)) {
        uVar4 = FUN_0004c924(param_1,param_2,0x52);
        uVar4 = FUN_0004eb66(param_1,param_2,uVar4);
        *(short *)(param_3 + 7) = (short)uVar4;
        *(char *)((int)param_3 + 0x1e) = (char)((uint)uVar4 >> 0x10);
        uVar4 = FUN_0004c924(param_1,param_2,0x54);
        param_3[0xe] = uVar4;
        iVar2 = FUN_0004c924(param_1,param_2,0x51);
        *(bool *)((int)param_3 + 0x3d) = iVar2 != 0;
      }
    }
  }
  return;
}

