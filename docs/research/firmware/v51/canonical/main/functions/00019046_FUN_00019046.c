/* Address: 00019046; name: FUN_00019046; body bytes: 64 */

void FUN_00019046(undefined4 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_00015ee8();
  if (param_2 < 300) {
    param_2 = 300;
  }
  *(short *)(iVar1 + 0x1c) = (short)param_2;
  uVar2 = ((param_2 << 8) / (uint)*(ushort *)(iVar1 + 0xc) + 500) / 1000 - 1;
  if (0xff < uVar2) {
    uVar2 = 0xff;
  }
  FUN_00012cb0(param_1,5,uVar2 & 0xff);
  return;
}

