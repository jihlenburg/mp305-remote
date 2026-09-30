/* Address: 0004a6cc; name: FUN_0004a6cc; body bytes: 296 */

void FUN_0004a6cc(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  FUN_0004e680(param_2,1);
  FUN_0004e624(param_2,0);
  *(undefined1 *)(param_2 + 0x68) = 0;
  *(undefined1 *)(param_2 + 0x69) = 0;
  *(byte *)(param_2 + 0x6a) = *(byte *)(param_2 + 0x6a) & 0xf0;
  FUN_0004a152(param_2 + 0x5c,4);
  uVar1 = FUN_0004b384(param_2);
  *(undefined4 *)(param_2 + 0x2c) = uVar1;
  FUN_0004aa6e(uVar1,1);
  *(undefined4 *)(param_2 + 0x44) = 0;
  *(undefined4 *)(param_2 + 0x4c) = 0;
  *(undefined4 *)(param_2 + 0x50) = 0;
  *(undefined4 *)(param_2 + 0x54) = 0;
  *(undefined4 *)(param_2 + 0x48) = 0;
  uVar1 = FUN_0004b144(&DAT_0007ac8c,param_2);
  FUN_0004b210();
  FUN_0004e654(uVar1,&DAT_20000064);
  FUN_0004e63c(uVar1,1);
  FUN_0004e624(uVar1,1);
  FUN_0004aa6e(uVar1,0x4000);
  FUN_0004e00e(uVar1,2);
  *(undefined4 *)(param_2 + 0x30) = uVar1;
  uVar1 = FUN_0004b144(&DAT_0007acb0,uVar1);
  FUN_0004b210();
  FUN_0004e84a(uVar1,&DAT_20000064,0x3fffffff);
  FUN_0004e624(uVar1,0);
  FUN_0004e5f4(uVar1,0,2);
  FUN_0004e00e(uVar1,2);
  FUN_0004aa6e(uVar1,0x4000);
  *(undefined4 *)(param_2 + 0x38) = uVar1;
  uVar1 = FUN_0003e808(uVar1);
  FUN_0004aa4c(uVar1,0x4a627,7,param_2);
  FUN_0004aa6e(uVar1,0x4000);
  FUN_0004e624(uVar1,0);
  *(undefined4 *)(param_2 + 0x3c) = uVar1;
  uVar1 = FUN_00047698(uVar1);
  FUN_00047d8e(uVar1,&DAT_0004a800);
  uVar1 = FUN_00048d88(*(undefined4 *)(param_2 + 0x38));
  FUN_0004aa6e(uVar1,1);
  *(undefined4 *)(param_2 + 0x34) = 0;
  *(undefined4 *)(param_2 + 0x40) = uVar1;
  *(undefined4 *)(param_2 + 0x58) = 0;
  FUN_0004aa4c(param_2,0x4a9e5,0x20);
  return;
}

