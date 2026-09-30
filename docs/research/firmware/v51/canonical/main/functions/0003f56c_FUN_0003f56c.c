/* Address: 0003f56c; name: FUN_0003f56c; body bytes: 82 */

void FUN_0003f56c(undefined4 param_1,int param_2)

{
  FUN_0004a152(param_2 + 0x2c,0x14);
  FUN_0004a152(param_2 + 0x38,0x18);
  *(undefined4 *)(param_2 + 0x44) = 0;
  *(undefined4 *)(param_2 + 0x54) = 0;
  *(undefined4 *)(param_2 + 0x48) = 0;
  *(undefined4 *)(param_2 + 0x58) = 0;
  *(undefined4 *)(param_2 + 0x4c) = 100;
  *(undefined4 *)(param_2 + 0x5c) = 100;
  *(undefined4 *)(param_2 + 0x50) = 100;
  *(undefined4 *)(param_2 + 0x60) = 100;
  *(undefined4 *)(param_2 + 0x68) = 3;
  *(undefined4 *)(param_2 + 0x6c) = 5;
  *(undefined4 *)(param_2 + 0x70) = 10;
  *(undefined4 *)(param_2 + 100) = 0x7fffffff;
  *(byte *)(param_2 + 0x74) = (*(byte *)(param_2 + 0x74) & 0xf8) + 1 & 0xf7;
  return;
}

