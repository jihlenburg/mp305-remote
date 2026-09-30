/* Address: 00047624; name: FUN_00047624; body bytes: 112 */

/* Recovered from stored Thumb pointer at 0007a720; callback identification is inferred until
   reviewed. */

void FUN_00047624(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  *(undefined4 *)(param_2 + 0x2c) = 0;
  *(uint *)(param_2 + 0x58) = *(uint *)(param_2 + 0x58) & 0xffffff83 | 3;
  uVar1 = FUN_0004ccf8(param_2);
  *(undefined4 *)(param_2 + 0x3c) = uVar1;
  uVar1 = FUN_0004bbec(param_2);
  *(undefined4 *)(param_2 + 0x40) = uVar1;
  *(undefined4 *)(param_2 + 0x44) = 0;
  *(undefined4 *)(param_2 + 0x48) = 0x100;
  *(undefined4 *)(param_2 + 0x4c) = 0x100;
  *(uint *)(param_2 + 0x58) = *(uint *)(param_2 + 0x58) | 0x80;
  FUN_0004f266(param_2 + 0x34,0);
  FUN_0004f266(param_2 + 0x50,&DAT_20000032,&DAT_20000032);
  *(uint *)(param_2 + 0x58) = (*(uint *)(param_2 + 0x58) & 0xfffff0ff) + 0x900;
  FUN_0004e00e(param_2,2);
  FUN_0004aa6e(param_2,0x10000);
  return;
}

