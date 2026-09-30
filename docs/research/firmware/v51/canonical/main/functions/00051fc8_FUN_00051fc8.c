/* Address: 00051fc8; name: FUN_00051fc8; body bytes: 158 */

/* Recovered from stored Thumb pointer at 0007af3c; callback identification is inferred until
   reviewed. */

void FUN_00051fc8(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  *(byte *)(param_2 + 0x70) = *(byte *)(param_2 + 0x70) & 0xfb;
  *(undefined4 *)(param_2 + 0x34) = 0;
  *(undefined4 *)(param_2 + 0x38) = 0;
  *(undefined4 *)(param_2 + 0x3c) = 0;
  *(undefined4 *)(param_2 + 0x40) = 0;
  *(undefined4 *)(param_2 + 0x44) = 0x5dc;
  *(byte *)(param_2 + 100) = *(byte *)(param_2 + 100) | 1;
  *(undefined4 *)(param_2 + 0x4c) = 1;
  *(byte *)(param_2 + 100) = *(byte *)(param_2 + 100) | 2;
  *(undefined4 *)(param_2 + 0x48) = 0;
  *(byte *)(param_2 + 0x70) = *(byte *)(param_2 + 0x70) & 0xf5;
  *(undefined4 *)(param_2 + 0x2c) = 0;
  *(undefined4 *)(param_2 + 0x30) = 0;
  uVar1 = FUN_00048d88(param_2);
  *(undefined4 *)(param_2 + 0x2c) = uVar1;
  uVar1 = FUN_0004f078(100);
  FUN_0004eae2(*(undefined4 *)(param_2 + 0x2c),uVar1);
  FUN_00049974(*(undefined4 *)(param_2 + 0x2c),&DAT_00052068);
  FUN_0004aa4c(*(undefined4 *)(param_2 + 0x2c),0x3bc85,0);
  FUN_0004aa6e(param_2,0x400);
  FUN_0004e00e(param_2,0x800);
  FUN_00052370(param_2,0);
  FUN_00060710(param_2);
  return;
}

