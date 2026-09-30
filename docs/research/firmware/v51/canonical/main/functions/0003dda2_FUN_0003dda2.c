/* Address: 0003dda2; name: FUN_0003dda2; body bytes: 52 */

void FUN_0003dda2(int *param_1,int *param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = *param_3;
  if (*param_2 < *param_3) {
    iVar1 = *param_2;
  }
  *param_1 = iVar1;
  iVar1 = param_3[1];
  if (param_2[1] < param_3[1]) {
    iVar1 = param_2[1];
  }
  param_1[1] = iVar1;
  iVar1 = param_3[2];
  if (param_3[2] < param_2[2]) {
    iVar1 = param_2[2];
  }
  param_1[2] = iVar1;
  iVar1 = param_2[3];
  if (param_2[3] <= param_3[3]) {
    iVar1 = param_3[3];
  }
  param_1[3] = iVar1;
  return;
}

