/* Address: 0003e078; name: FUN_0003e078; body bytes: 90 */

void FUN_0003e078(undefined4 param_1,int param_2)

{
  *(undefined4 *)(param_2 + 0x30) = 0;
  *(undefined4 *)(param_2 + 0x34) = 100;
  *(undefined4 *)(param_2 + 0x38) = 0;
  *(undefined4 *)(param_2 + 0x2c) = 0;
  *(undefined4 *)(param_2 + 0x3c) = 0;
  *(undefined4 *)(param_2 + 0x44) = 0;
  *(undefined4 *)(param_2 + 0x40) = 0;
  *(undefined4 *)(param_2 + 0x48) = 0;
  *(byte *)(param_2 + 0x70) = *(byte *)(param_2 + 0x70) & 0xc0;
  *(undefined1 *)(param_2 + 0x4c) = 0;
  FUN_0003e1ee(param_2,param_2 + 0x50);
  FUN_0003e1ee(param_2,param_2 + 0x60);
  FUN_0004e00e(param_2,8);
  FUN_0004e00e(param_2,0x10);
  FUN_0003e26c(param_2,0);
  return;
}

