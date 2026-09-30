/* Address: 00036b7c; name: FUN_00036b7c; body bytes: 50 */

void FUN_00036b7c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 *param_5)

{
  int iVar1;
  
  if (param_5 != (undefined4 *)0x0) {
    *param_5 = 0;
  }
  iVar1 = FUN_00046f3c(param_1,param_2,0);
  if (iVar1 == 0) {
    FUN_00046d6e(param_1,param_3,param_4,param_5);
    return;
  }
  return;
}

