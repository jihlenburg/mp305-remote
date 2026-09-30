/* Address: 00046c30; name: FUN_00046c30; body bytes: 66 */

undefined4 FUN_00046c30(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = param_1[1];
  if (iVar1 == 0) {
    return 0xb;
  }
  if (*(code **)(iVar1 + 0x10) != (code *)0x0) {
    uVar2 = (**(code **)(iVar1 + 0x10))(iVar1,*param_1);
    if ((*(int *)(param_1[1] + 4) != 0) && (param_1[2] != 0)) {
      if ((*(int *)(param_1[1] + 4) != -1) && (*(int *)(param_1[2] + 0xc) != 0)) {
        FUN_00046bec();
      }
      FUN_00046bec(param_1[2]);
    }
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    return uVar2;
  }
  return 9;
}

