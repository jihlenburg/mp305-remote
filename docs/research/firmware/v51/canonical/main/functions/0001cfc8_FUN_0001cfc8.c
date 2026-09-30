/* Address: 0001cfc8; name: FUN_0001cfc8; body bytes: 112 */

void FUN_0001cfc8(undefined4 param_1,uint param_2,uint param_3,uint param_4,int param_5)

{
  int iVar1;
  short sVar2;
  
  iVar1 = FUN_00015ee8();
  *(byte *)(iVar1 + 5) =
       (byte)((param_2 & 1) << 4) | 0x20 | (byte)((param_3 & 3) << 2) | (byte)((param_4 & 1) << 1) |
       (byte)param_5 & 1;
  if (param_3 == 1) {
    sVar2 = (ushort)*(byte *)(iVar1 + 2) * 6;
  }
  else {
    sVar2 = (ushort)*(byte *)(iVar1 + 2) * 0xc;
  }
  *(short *)(iVar1 + 0xc) = sVar2;
  if (param_2 == 0) {
    sVar2 = (ushort)*(byte *)(iVar1 + 1) * 6;
  }
  else {
    sVar2 = (ushort)*(byte *)(iVar1 + 1) * 0xc;
  }
  *(short *)(iVar1 + 0xe) = sVar2;
  if (param_5 == 0) {
    *(undefined2 *)(iVar1 + 0x10) = 0x7d;
  }
  else {
    *(undefined2 *)(iVar1 + 0x10) = 0x32;
  }
  if (param_4 == 0) {
    *(undefined2 *)(iVar1 + 0x12) = 0x7d;
  }
  else {
    *(undefined2 *)(iVar1 + 0x12) = 0x32;
  }
  FUN_00012cb0(param_1,8);
  return;
}

