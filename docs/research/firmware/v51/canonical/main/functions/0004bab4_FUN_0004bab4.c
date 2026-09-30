/* Address: 0004bab4; name: FUN_0004bab4; body bytes: 68 */

void FUN_0004bab4(undefined4 param_1,int *param_2)

{
  int iVar1;
  
  FUN_0004bb3c();
  iVar1 = FUN_0004c9e8(param_1,0);
  *param_2 = iVar1 + *param_2;
  iVar1 = FUN_0004ca46(param_1,0);
  param_2[2] = param_2[2] - iVar1;
  iVar1 = FUN_0004caa4(param_1,0);
  param_2[1] = iVar1 + param_2[1];
  iVar1 = FUN_0004c98a(param_1,0);
  param_2[3] = param_2[3] - iVar1;
  return;
}

