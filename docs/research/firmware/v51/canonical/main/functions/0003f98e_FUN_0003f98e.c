/* Address: 0003f98e; name: FUN_0003f98e; body bytes: 22 */

void FUN_0003f98e(int param_1,int param_2,int param_3)

{
  if ((*(int *)(param_1 + 0x68) == param_2) && (*(int *)(param_1 + 0x6c) == param_3)) {
    return;
  }
  *(int *)(param_1 + 0x68) = param_2;
  *(int *)(param_1 + 0x6c) = param_3;
  FUN_0004d3d8();
  return;
}

