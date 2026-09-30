/* Address: 0004ce8c; name: FUN_0004ce8c; body bytes: 180 */

void FUN_0004ce8c(int param_1,int param_2,int *param_3,undefined4 param_4)

{
  byte bVar1;
  undefined1 uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  
  *param_3 = param_1;
  param_3[1] = param_2;
  bVar1 = FUN_0004c924(param_1,param_2,0x44,param_4,param_4);
  *(byte *)(param_3 + 0x13) = bVar1;
  if (2 < bVar1) {
    uVar3 = FUN_0004c774(param_1,param_2);
    if (uVar3 < 0xfd) {
      *(char *)(param_3 + 0x13) =
           (char)((uint)((int)(short)(ushort)*(byte *)(param_3 + 0x13) * (int)(short)uVar3) >> 8);
    }
    if (2 < *(byte *)(param_3 + 0x13)) {
      param_3[0xb] = 0;
      param_3[0xc] = 0x100;
      param_3[0xd] = 0x100;
      iVar4 = FUN_0003db28();
      param_3[0x10] = iVar4 / 2;
      iVar4 = FUN_0003db0a(param_1 + 0x14);
      param_3[0x11] = iVar4 / 2;
      uVar2 = FUN_0004c924(param_1,param_2,0x46);
      *(undefined1 *)((int)param_3 + 0x4b) = uVar2;
      uVar5 = FUN_0004c924(param_1,param_2,0x45);
      uVar5 = FUN_0004eb66(param_1,param_2,uVar5);
      *(short *)(param_3 + 0x12) = (short)uVar5;
      *(char *)((int)param_3 + 0x4a) = (char)((uint)uVar5 >> 0x10);
      if (param_2 != 0) {
        bVar1 = FUN_0004c62c(param_1,param_2);
        *(byte *)((int)param_3 + 0x4d) = *(byte *)((int)param_3 + 0x4d) & 0xf0 | bVar1 & 0xf;
      }
    }
  }
  return;
}

