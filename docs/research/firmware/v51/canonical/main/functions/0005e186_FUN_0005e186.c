/* Address: 0005e186; name: FUN_0005e186; body bytes: 100 */

void FUN_0005e186(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = FUN_0004bb48(*param_1);
  FUN_0004e5a6(*(undefined4 *)(iVar1 + 0x2c0),0x2c,0);
  FUN_0004e5a6(*(undefined4 *)(iVar1 + 0x2c8),0x2d,0);
  if ((*(int *)(iVar1 + 0x2c8) != 0) && ((int)((uint)*(byte *)(iVar1 + 0x2d4) << 0x1e) < 0)) {
    FUN_0004b3a0();
  }
  *(undefined4 *)(iVar1 + 0x2c8) = 0;
  *(byte *)(iVar1 + 0x2d4) = *(byte *)(iVar1 + 0x2d4) & 0xfe;
  *(undefined4 *)(iVar1 + 0x2cc) = 0;
  FUN_0004e088(*param_1,0x5f,0);
  FUN_0004d3d8(*(undefined4 *)(iVar1 + 0x2c0));
  return;
}

