/* Address: 00063fb0; name: FUN_00063fb0; body bytes: 170 */

void FUN_00063fb0(int param_1,int param_2,int param_3,int *param_4,int *param_5)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x18);
  if (((*(int *)(param_1 + 0x20) == 0) && (iVar1 == 0x100)) && (*(int *)(param_1 + 0x1c) == 0x100))
  {
    *param_4 = param_2 << 8;
    param_3 = param_3 << 8;
  }
  else {
    param_2 = param_2 - *(int *)(param_1 + 0x2c);
    param_3 = param_3 - *(int *)(param_1 + 0x30);
    if (*(int *)(param_1 + 0x20) == 0) {
      *param_4 = (param_2 * 0x10000) / iVar1 + *(int *)(param_1 + 0x24);
      param_3 = *(int *)(param_1 + 0x28) + (param_3 * 0x10000) / *(int *)(param_1 + 0x1c);
    }
    else {
      if ((iVar1 == 0x100) && (*(int *)(param_1 + 0x1c) == 0x100)) {
        *param_4 = *(int *)(param_1 + 0x24) +
                   (param_2 * *(int *)(param_1 + 0x14) - *(int *)(param_1 + 0x10) * param_3 >> 2);
        iVar1 = *(int *)(param_1 + 0x14) * param_3 + param_2 * *(int *)(param_1 + 0x10);
      }
      else {
        *param_4 = *(int *)(param_1 + 0x24) +
                   (((param_2 * *(int *)(param_1 + 0x14) - *(int *)(param_1 + 0x10) * param_3) *
                    0x100) / iVar1 >> 2);
        iVar1 = ((*(int *)(param_1 + 0x14) * param_3 + param_2 * *(int *)(param_1 + 0x10)) * 0x100)
                / *(int *)(param_1 + 0x1c);
      }
      param_3 = *(int *)(param_1 + 0x28) + (iVar1 >> 2);
    }
  }
  *param_5 = param_3;
  return;
}

