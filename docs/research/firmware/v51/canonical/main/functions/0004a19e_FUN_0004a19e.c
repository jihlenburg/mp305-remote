/* Address: 0004a19e; name: FUN_0004a19e; body bytes: 98 */

int FUN_0004a19e(int *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((param_1 == (int *)0x0) || (param_2 == 0)) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_0004a118();
    if (iVar1 == param_2) {
      iVar1 = FUN_0004a162(param_1);
    }
    else {
      iVar1 = FUN_0004a318(*param_1 + 8);
      if (iVar1 != 0) {
        uVar2 = *(undefined4 *)(*param_1 + param_2);
        FUN_00054110(param_1,uVar2,iVar1);
        FUN_0005411c(param_1,iVar1,uVar2);
        FUN_0005411c(param_1,param_2,iVar1);
        FUN_00054110(param_1,iVar1,param_2);
      }
    }
  }
  return iVar1;
}

