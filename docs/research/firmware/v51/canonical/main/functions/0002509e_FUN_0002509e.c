/* Address: 0002509e; name: FUN_0002509e; body bytes: 56 */

undefined4 FUN_0002509e(int *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = (**(code **)(*param_1 + 0x20))(param_1);
  if (iVar1 != 0) {
    (**(code **)(*param_1 + 0x14))(param_1,iVar1,param_2);
    uVar2 = FUN_0003f16a(iVar1);
    (*(code *)param_1[6])(uVar2,param_2);
    FUN_0003f158(iVar1);
    return 1;
  }
  return 0;
}

