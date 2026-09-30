/* Address: 00054110; name: FUN_00054110; body bytes: 12 */

void FUN_00054110(int *param_1,int param_2,undefined4 param_3)

{
  if (param_2 != 0) {
    *(undefined4 *)(*param_1 + param_2 + 4) = param_3;
  }
  return;
}

