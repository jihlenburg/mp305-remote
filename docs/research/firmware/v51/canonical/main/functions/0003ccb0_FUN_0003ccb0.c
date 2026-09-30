/* Address: 0003ccb0; name: FUN_0003ccb0; body bytes: 126 */

/* Recovered from stored Thumb pointer at 0007a578; callback identification is inferred until
   reviewed. */

void FUN_0003ccb0(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  
  *(undefined4 *)(param_2 + 0x2c) = 0;
  *(undefined4 *)(param_2 + 0x38) = 0x43070000;
  *(undefined4 *)(param_2 + 0x3c) = 0x42340000;
  *(undefined4 *)(param_2 + 0x30) = 0x43070000;
  *(undefined4 *)(param_2 + 0x34) = 0x43870000;
  *(uint *)(param_2 + 0x4c) = *(uint *)(param_2 + 0x4c) & 0xfffffff9;
  *(undefined4 *)(param_2 + 0x40) = 0xffff8000;
  uVar2 = *(uint *)(param_2 + 0x4c);
  *(undefined4 *)(param_2 + 0x44) = 0;
  *(undefined4 *)(param_2 + 0x48) = 100;
  *(uint *)(param_2 + 0x4c) = uVar2 | 8;
  *(uint *)(param_2 + 0x4c) = uVar2 & 0xfffffffe | 8;
  *(undefined4 *)(param_2 + 0x50) = 0x2d0;
  uVar1 = FUN_00052708();
  *(undefined4 *)(param_2 + 0x54) = uVar1;
  *(undefined4 *)(param_2 + 0x58) = *(undefined4 *)(param_2 + 0x34);
  *(uint *)(param_2 + 0x4c) = *(uint *)(param_2 + 0x4c) & 0xffffffef;
  FUN_0004aa6e(param_2,2);
  FUN_0004e00e(param_2,0x310);
  FUN_0004e5e4(param_2,0xd);
  return;
}

