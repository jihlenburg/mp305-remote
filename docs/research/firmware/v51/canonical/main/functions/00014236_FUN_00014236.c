/* Address: 00014236; name: FUN_00014236; body bytes: 24 */

void FUN_00014236(int param_1,int param_2,int param_3)

{
  ushort uVar1;
  
  uVar1 = (ushort)(1 << (param_2 + 0xeU & 0xff));
  if (param_3 == 1) {
    uVar1 = *(ushort *)(param_1 + 0x1c) & ~uVar1;
  }
  else {
    uVar1 = *(ushort *)(param_1 + 0x1c) | uVar1;
  }
  *(ushort *)(param_1 + 0x1c) = uVar1;
  return;
}

