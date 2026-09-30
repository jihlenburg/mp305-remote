/* Address: 0005e4e8; name: FUN_0005e4e8; body bytes: 80 */

void FUN_0005e4e8(int param_1,int *param_2,int *param_3)

{
  if (param_3 != (int *)0x0) {
    if (*(int *)(param_1 + 0x54) + *param_3 < *(int *)(param_1 + 0x80)) {
      *param_3 = *(int *)(param_1 + 0x80) - *(int *)(param_1 + 0x54);
    }
    if (*(int *)(param_1 + 0x88) < *(int *)(param_1 + 0x54) + *param_3) {
      *param_3 = *(int *)(param_1 + 0x88) - *(int *)(param_1 + 0x54);
    }
  }
  if (param_2 != (int *)0x0) {
    if (*(int *)(param_1 + 0x50) + *param_2 < *(int *)(param_1 + 0x7c)) {
      *param_2 = *(int *)(param_1 + 0x7c) - *(int *)(param_1 + 0x50);
    }
    if (*(int *)(param_1 + 0x84) < *param_2 + *(int *)(param_1 + 0x50)) {
      *param_2 = *(int *)(param_1 + 0x84) - *(int *)(param_1 + 0x50);
    }
  }
  return;
}

