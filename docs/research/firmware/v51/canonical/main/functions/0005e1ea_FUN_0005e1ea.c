/* Address: 0005e1ea; name: FUN_0005e1ea; body bytes: 38 */

void FUN_0005e1ea(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0004bb48(*param_1);
  *(undefined4 *)(iVar1 + 0x2c8) = *(undefined4 *)(iVar1 + 0x2c0);
  uVar2 = *param_1;
  *(undefined4 *)(iVar1 + 0x2c0) = uVar2;
  FUN_0004e5a6(uVar2,0x2b,0);
  return;
}

