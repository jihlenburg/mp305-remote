/* Address: 00018ffc; name: FUN_00018ffc; body bytes: 74 */

void FUN_00018ffc(undefined4 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_00015ee8();
  if (param_2 < 300) {
    param_2 = 300;
  }
  if (*(ushort *)(iVar1 + 0x1e) != param_2) {
    *(short *)(iVar1 + 0x1e) = (short)param_2;
    if ((param_2 == 0) ||
       (uVar2 = ((param_2 << 8) / (uint)*(ushort *)(iVar1 + 0xe) + 500) / 1000 - 1, 0xff < uVar2)) {
      uVar2 = 0xff;
    }
    FUN_00012cb0(param_1,6,uVar2 & 0xff);
    return;
  }
  return;
}

