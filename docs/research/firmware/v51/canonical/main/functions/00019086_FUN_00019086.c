/* Address: 00019086; name: FUN_00019086; body bytes: 144 */

void FUN_00019086(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_00015ee8();
  *(short *)(iVar1 + 0x18) = (short)param_2;
  if ((int)((uint)*(byte *)(iVar1 + 7) << 0x1b) < 0) {
    uVar2 = ((uint)(param_2 * 500) / 1000 + 5) / 10 - 1;
    if (0x3ff < uVar2) {
      uVar2 = 0x3ff;
    }
    uVar2 = uVar2 << 6;
    FUN_00012cb0(param_1,3,(uVar2 & 0xffff) >> 8);
    uVar3 = 4;
  }
  else {
    iVar1 = FUN_00015ee8(param_1);
    uVar2 = ((uint)(param_2 * 0x32) / (uint)*(ushort *)(iVar1 + 0x10) + 5) / 10 - 1;
    if (0x3ff < uVar2) {
      uVar2 = 0x3ff;
    }
    uVar2 = uVar2 << 6;
    FUN_00012cb0(param_1,1,(uVar2 & 0xffff) >> 8);
    uVar3 = 2;
  }
  FUN_00012cb0(param_1,uVar3,uVar2 & 0xc0);
  return;
}

