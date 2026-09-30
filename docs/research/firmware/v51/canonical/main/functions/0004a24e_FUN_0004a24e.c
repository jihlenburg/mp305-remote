/* Address: 0004a24e; name: FUN_0004a24e; body bytes: 94 */

void FUN_0004a24e(int *param_1,int param_2,int param_3)

{
  int iVar1;
  
  if (param_2 != param_3) {
    if (param_3 == 0) {
      iVar1 = FUN_0004a14a();
    }
    else {
      iVar1 = *(int *)(*param_1 + param_3);
    }
    if (param_2 != iVar1) {
      FUN_0004a2ac(param_1,param_2);
      FUN_00054110(param_1,iVar1,param_2);
      FUN_0005411c(param_1,param_2,iVar1);
      FUN_0005411c(param_1,param_3,param_2);
      FUN_00054110(param_1,param_2,param_3);
      if (param_3 == 0) {
        param_1[2] = param_2;
      }
      if (iVar1 == 0) {
        param_1[1] = param_2;
      }
    }
  }
  return;
}

