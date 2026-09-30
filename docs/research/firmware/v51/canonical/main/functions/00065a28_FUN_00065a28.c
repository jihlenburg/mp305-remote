/* Address: 00065a28; name: FUN_00065a28; body bytes: 62 */

void FUN_00065a28(int *param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  
  *(uint *)(DAT_1ffe0000 + 0x18) = param_2 | 0x80000000;
  iVar1 = param_1[1];
  *(int *)(DAT_1ffe0000 + 0x1c) = iVar1;
  *(undefined4 *)(DAT_1ffe0000 + 0x20) = *(undefined4 *)(iVar1 + 8);
  *(int *)(*(int *)(iVar1 + 8) + 4) = DAT_1ffe0000 + 0x18;
  *(int *)(iVar1 + 8) = DAT_1ffe0000 + 0x18;
  *(int **)(DAT_1ffe0000 + 0x28) = param_1;
  *param_1 = *param_1 + 1;
  FUN_0005982c(param_3,1);
  return;
}

