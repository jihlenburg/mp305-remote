/* Address: 0004a162; name: FUN_0004a162; body bytes: 60 */

int FUN_0004a162(int *param_1)

{
  int iVar1;
  
  iVar1 = FUN_0004a318(*param_1 + 8);
  if (iVar1 != 0) {
    FUN_0005411c(param_1,iVar1,0);
    FUN_00054110(param_1,iVar1,param_1[1]);
    if (param_1[1] != 0) {
      FUN_0005411c(param_1,param_1[1],iVar1);
    }
    param_1[1] = iVar1;
    if (param_1[2] == 0) {
      param_1[2] = iVar1;
    }
  }
  return iVar1;
}

