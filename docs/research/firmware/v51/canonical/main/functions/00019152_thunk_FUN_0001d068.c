/* Address: 00019152; name: thunk_FUN_0001d068; body bytes: 4 */

void thunk_FUN_0001d068(undefined4 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_00015ee8();
  if ((param_2 < 12000) && (-1 < (int)((uint)*(byte *)(iVar1 + 6) << 0x1b))) {
    uVar3 = 1;
  }
  else {
    if ((param_2 < 0x2711) || (-1 < (int)((uint)*(byte *)(iVar1 + 6) << 0x1b))) goto LAB_0001d09c;
    uVar3 = 0;
  }
  FUN_0001d038(param_1,uVar3);
LAB_0001d09c:
  uVar2 = ((param_2 * 10) / (uint)*(ushort *)(iVar1 + 10) + 5) / 10 - 1;
  if (0xff < uVar2) {
    uVar2 = 0xff;
  }
  *(short *)(iVar1 + 0x14) = (short)param_2;
  FUN_00012cb0(param_1,7,uVar2 & 0xff);
  return;
}

