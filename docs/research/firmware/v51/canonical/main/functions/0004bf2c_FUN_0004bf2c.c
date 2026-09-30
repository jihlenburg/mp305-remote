/* Address: 0004bf2c; name: FUN_0004bf2c; body bytes: 12 */

int FUN_0004bf2c(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  if (*(int *)(param_1 + 8) != 0) {
    iVar1 = -*(int *)(*(int *)(param_1 + 8) + 0x1c);
  }
  return iVar1;
}

