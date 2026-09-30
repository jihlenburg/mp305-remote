/* Address: 0004a60a; name: FUN_0004a60a; body bytes: 28 */

undefined4 FUN_0004a60a(int param_1,int param_2)

{
  if ((*(int *)(param_1 + 0x50) != param_2) &&
     ((*(int *)(param_1 + 0x3c) != param_2 || (1 < *(byte *)(param_1 + 0x69))))) {
    return 0;
  }
  return 1;
}

