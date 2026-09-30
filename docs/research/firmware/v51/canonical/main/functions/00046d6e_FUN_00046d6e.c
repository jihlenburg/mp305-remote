/* Address: 00046d6e; name: FUN_00046d6e; body bytes: 92 */

undefined4
FUN_00046d6e(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_1c;
  
  if (param_4 != (undefined4 *)0x0) {
    *param_4 = 0;
  }
  iVar2 = param_1[1];
  if (iVar2 == 0) {
    return 0xb;
  }
  if (*(int *)(iVar2 + 4) == 0) {
    iVar2 = *(int *)(iVar2 + 0x14);
  }
  else {
    if (*(int *)(iVar2 + 0x14) == 0) {
      return 9;
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
  }
  if (iVar2 == 0) {
    return 9;
  }
  local_1c = 0;
  iVar2 = param_1[1];
  if (*(int *)(iVar2 + 4) == 0) {
    uVar1 = (**(code **)(iVar2 + 0x14))(iVar2,*param_1,param_2,param_3,&local_1c);
  }
  else {
    uVar1 = FUN_00046dca(param_1,param_2,param_3,&local_1c,param_3);
  }
  if (param_4 != (undefined4 *)0x0) {
    *param_4 = local_1c;
    return uVar1;
  }
  return uVar1;
}

