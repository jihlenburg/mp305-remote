/* Address: 00045fd0; name: FUN_00045fd0; body bytes: 98 */

/* Recovered from stored Thumb pointer at 0007a6d8; callback identification is inferred until
   reviewed. */

void FUN_00045fd0(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  *(undefined4 *)(param_2 + 0x2c) = 0;
  *(undefined **)(param_2 + 0x34) = &DAT_00046034;
  *(undefined4 *)(param_2 + 0x38) = 0;
  *(undefined4 *)(param_2 + 0x30) = 0;
  *(byte *)(param_2 + 0x4c) = *(byte *)(param_2 + 0x4c) | 0x30;
  *(undefined4 *)(param_2 + 0x40) = 0;
  *(undefined4 *)(param_2 + 0x44) = 0;
  *(undefined4 *)(param_2 + 0x48) = 0xffff;
  *(undefined4 *)(param_2 + 0x3c) = 0;
  *(byte *)(param_2 + 0x4c) = (*(byte *)(param_2 + 0x4c) & 0xf0) + 8;
  FUN_0004aa6e(param_2,0x400);
  FUN_00046572(param_2,"Option 1\nOption 2\nOption 3");
  uVar1 = FUN_0004bc94(param_2);
  iVar2 = FUN_0004b144(&PTR_DAT_0007a6f8,uVar1);
  FUN_0004b210();
  *(int *)(param_2 + 0x2c) = iVar2;
  *(int *)(iVar2 + 0x2c) = param_2;
  return;
}

