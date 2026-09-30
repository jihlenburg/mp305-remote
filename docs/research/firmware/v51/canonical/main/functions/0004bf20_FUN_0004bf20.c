/* Address: 0004bf20; name: FUN_0004bf20; body bytes: 12 */

int FUN_0004bf20(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  if (*(int *)(param_1 + 8) != 0) {
    iVar1 = -*(int *)(*(int *)(param_1 + 8) + 0x18);
  }
  return iVar1;
}

