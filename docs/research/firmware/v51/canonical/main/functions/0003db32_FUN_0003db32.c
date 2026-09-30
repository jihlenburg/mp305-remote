/* Address: 0003db32; name: FUN_0003db32; body bytes: 26 */

void FUN_0003db32(int *param_1,int param_2,int param_3)

{
  *param_1 = *param_1 - param_2;
  param_1[2] = param_2 + param_1[2];
  param_1[1] = param_1[1] - param_3;
  param_1[3] = param_1[3] + param_3;
  return;
}

