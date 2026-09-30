/* Address: 00048d20; name: FUN_00048d20; body bytes: 94 */

/* Recovered from stored Thumb pointer at 0007aae0; callback identification is inferred until
   reviewed. */

void FUN_00048d20(undefined4 param_1,int param_2)

{
  *(undefined4 *)(param_2 + 0x2c) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0xffffffff;
  *(byte *)(param_2 + 0x5c) = *(byte *)(param_2 + 0x5c) & 0xf0;
  FUN_0004f266(param_2 + 0x54,0,0);
  *(undefined4 *)(param_2 + 0x40) = 0;
  *(undefined4 *)(param_2 + 0x44) = 0xffff;
  *(undefined4 *)(param_2 + 0x48) = 0xffff;
  *(undefined4 *)(param_2 + 0x38) = 0xffffffff;
  *(undefined4 *)(param_2 + 0x3c) = 0;
  *(undefined4 *)(param_2 + 0x30) = 0;
  *(byte *)(param_2 + 0x5c) = *(byte *)(param_2 + 0x5c) & 0xdf;
  FUN_0004e00e(param_2,2);
  FUN_000498fc(param_2,0);
  FUN_00049974(param_2,&DAT_00048d80);
  return;
}

