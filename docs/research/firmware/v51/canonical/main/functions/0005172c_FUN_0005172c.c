/* Address: 0005172c; name: FUN_0005172c; body bytes: 42 */

void FUN_0005172c(int param_1,int *param_2,undefined4 *param_3,int *param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00051cb0(param_1,param_4);
  *param_2 = iVar1;
  uVar2 = 0;
  if (iVar1 != 0) {
    uVar2 = FUN_00051cb0(*param_4 + param_1,0);
  }
  *param_3 = uVar2;
  return;
}

