/* Address: 0002641a; name: FUN_0002641a; body bytes: 84 */

void FUN_0002641a(int *param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7)

{
  int iVar1;
  int iVar2;
  
  if (param_2 == 2) {
    iVar2 = FUN_00051a28(param_3,param_4,param_5,param_6);
    iVar1 = FUN_0003db28(param_7);
    iVar2 = iVar1 / 2 - iVar2 / 2;
  }
  else {
    if (param_2 != 3) {
      return;
    }
    iVar1 = FUN_00051a28(param_3,param_4,param_5,param_6);
    iVar2 = FUN_0003db28(param_7);
    iVar2 = iVar2 - iVar1;
  }
  *param_1 = iVar2 + *param_1;
  return;
}

