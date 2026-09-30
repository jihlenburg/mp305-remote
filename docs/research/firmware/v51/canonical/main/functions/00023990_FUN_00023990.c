/* Address: 00023990; name: FUN_00023990; body bytes: 42 */

void FUN_00023990(undefined4 param_1,int *param_2)

{
  int *piVar1;
  
  piVar1 = (int *)*param_2;
  if ((*piVar1 != 0) && (piVar1[8] << 0xb < 0)) {
    *param_2 = *piVar1;
    FUN_00023990(param_1,param_2);
  }
  *param_2 = (int)piVar1;
  FUN_00023970(param_1,param_2);
  return;
}

