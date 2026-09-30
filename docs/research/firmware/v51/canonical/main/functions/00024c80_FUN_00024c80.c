/* Address: 00024c80; name: FUN_00024c80; body bytes: 26 */

void FUN_00024c80(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_00024bd4();
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 2;
  *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | 1;
  return;
}

