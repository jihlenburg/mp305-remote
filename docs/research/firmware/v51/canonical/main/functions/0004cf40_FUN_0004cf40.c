/* Address: 0004cf40; name: FUN_0004cf40; body bytes: 180 */

void FUN_0004cf40(undefined4 param_1,int param_2,undefined4 *param_3,undefined4 param_4)

{
  byte bVar1;
  undefined1 uVar2;
  uint uVar3;
  undefined4 uVar4;
  
  *param_3 = param_1;
  param_3[1] = param_2;
  bVar1 = FUN_0004c924(param_1,param_2,0x59,param_4,param_4);
  *(byte *)(param_3 + 0x12) = bVar1;
  if (2 < bVar1) {
    uVar3 = FUN_0004c774(param_1,param_2);
    if (uVar3 < 0xfd) {
      *(char *)(param_3 + 0x12) =
           (char)((uint)((int)(short)(ushort)*(byte *)(param_3 + 0x12) * (int)(short)uVar3) >> 8);
    }
    if (2 < *(byte *)(param_3 + 0x12)) {
      uVar4 = FUN_0004cb08(param_1,param_2);
      *(short *)(param_3 + 0xb) = (short)uVar4;
      *(char *)((int)param_3 + 0x2e) = (char)((uint)uVar4 >> 0x10);
      uVar4 = FUN_0004c924(param_1,param_2,0x5b);
      param_3[0xf] = uVar4;
      uVar4 = FUN_0004c924(param_1,param_2,0x5c);
      param_3[0xe] = uVar4;
      bVar1 = FUN_0004c924(param_1,param_2,0x5d);
      *(byte *)(param_3 + 0x13) = *(byte *)(param_3 + 0x13) & 0xf8 | bVar1 & 7;
      if (param_2 != 0) {
        bVar1 = FUN_0004c62c(param_1,param_2);
        *(byte *)(param_3 + 0x13) = *(byte *)(param_3 + 0x13) & 199 | (bVar1 & 7) << 3;
      }
      uVar4 = FUN_0004cb22(param_1,param_2);
      param_3[8] = uVar4;
      uVar2 = FUN_0004c924(param_1,param_2,0x5e);
      *(undefined1 *)((int)param_3 + 0x4a) = uVar2;
    }
  }
  return;
}

