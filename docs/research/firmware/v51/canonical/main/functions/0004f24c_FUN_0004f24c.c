/* Address: 0004f24c; name: FUN_0004f24c; body bytes: 26 */

void FUN_0004f24c(int *param_1,float *param_2)

{
  float fVar1;
  
  fVar1 = param_2[1];
  *param_1 = (int)*param_2;
  param_1[1] = (int)fVar1;
  return;
}

