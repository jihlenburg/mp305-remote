/* Address: 000659e8; name: FUN_000659e8; body bytes: 58 */

void FUN_000659e8(int *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  iVar1 = param_1[1];
  *(int *)(DAT_1ffe0000 + 0x1c) = iVar1;
  *(undefined4 *)(DAT_1ffe0000 + 0x20) = *(undefined4 *)(iVar1 + 8);
  *(int *)(*(int *)(iVar1 + 8) + 4) = DAT_1ffe0000 + 0x18;
  *(int *)(iVar1 + 8) = DAT_1ffe0000 + 0x18;
  *(int **)(DAT_1ffe0000 + 0x28) = param_1;
  *param_1 = *param_1 + 1;
  if (param_3 != 0) {
    param_2 = 0xffffffff;
  }
  FUN_0005982c(param_2,param_3);
  return;
}

