/* Address: 0004fbae; name: FUN_0004fbae; body bytes: 92 */

void FUN_0004fbae(undefined4 param_1,int param_2)

{
  FUN_0004a152(param_2 + 0x2c,0x3c);
  *(uint *)(param_2 + 0x48) = (*(uint *)(param_2 + 0x48) & 0xffff8000) + 0xb & 0xc0007fff | 0x28000;
  *(undefined1 *)(param_2 + 0x3c) = 1;
  *(uint *)(param_2 + 0x48) = *(uint *)(param_2 + 0x48) | 0x40000000;
  *(undefined4 *)(param_2 + 0x50) = 0x10e;
  *(undefined4 *)(param_2 + 0x54) = 0x87;
  *(undefined4 *)(param_2 + 0x40) = 0;
  *(undefined4 *)(param_2 + 0x44) = 100;
  *(undefined4 *)(param_2 + 0x5c) = 0;
  *(undefined4 *)(param_2 + 0x60) = 0;
  *(uint *)(param_2 + 0x48) = *(uint *)(param_2 + 0x48) & 0x7fffffff;
  *(undefined4 *)(param_2 + 0x4c) = 0;
  *(undefined4 *)(param_2 + 0x58) = 0;
  *(undefined4 *)(param_2 + 0x38) = 0;
  FUN_0004e00e(param_2,0x10);
  return;
}

