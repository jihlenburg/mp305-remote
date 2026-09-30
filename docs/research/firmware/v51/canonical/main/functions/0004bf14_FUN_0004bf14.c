/* Address: 0004bf14; name: FUN_0004bf14; body bytes: 12 */

int FUN_0004bf14(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  if (*(int *)(param_1 + 8) != 0) {
    iVar1 = -*(int *)(*(int *)(param_1 + 8) + 0x1c);
  }
  return iVar1;
}

