/* Address: 00051f94; name: FUN_00051f94; body bytes: 56 */

void FUN_00051f94(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_000491f0(*(undefined4 *)(param_1 + 0x2c));
  if ((iVar1 == 0xffff) && (iVar1 = FUN_000491ec(*(undefined4 *)(param_1 + 0x2c)), iVar1 == 0xffff))
  {
    return;
  }
  FUN_00049a34(*(undefined4 *)(param_1 + 0x2c),0xffff);
  *(undefined4 *)(*(int *)(param_1 + 0x2c) + 0x48) = 0xffff;
  FUN_0004d3d8();
  return;
}

