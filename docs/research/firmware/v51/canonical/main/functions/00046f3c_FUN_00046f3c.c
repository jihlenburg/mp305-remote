/* Address: 00046f3c; name: FUN_00046f3c; body bytes: 106 */

int FUN_00046f3c(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  code *UNRECOVERED_JUMPTABLE;
  undefined4 local_18;
  
  iVar2 = param_1[1];
  if (iVar2 == 0) {
    return 0xb;
  }
  UNRECOVERED_JUMPTABLE = *(code **)(iVar2 + 0x1c);
  local_18 = param_4;
  if (*(int *)(iVar2 + 4) == 0) {
    if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00046f92. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      iVar2 = (*UNRECOVERED_JUMPTABLE)(iVar2,*param_1);
      return iVar2;
    }
  }
  else if ((UNRECOVERED_JUMPTABLE != (code *)0x0) && (*(int *)(iVar2 + 0x20) != 0)) {
    iVar1 = 0;
    if (param_3 == 0) {
      iVar2 = param_1[2];
    }
    else {
      if (param_3 != 1) {
        if (((param_3 == 2) && (iVar1 = (*UNRECOVERED_JUMPTABLE)(iVar2,*param_1), iVar1 == 0)) &&
           (iVar1 = (**(code **)(param_1[1] + 0x20))(param_1[1],*param_1,&local_18), iVar1 == 0)) {
          *(undefined4 *)(param_1[2] + 8) = local_18;
        }
        return iVar1;
      }
      iVar2 = param_1[2];
      param_2 = param_2 + *(int *)(iVar2 + 8);
    }
    *(int *)(iVar2 + 8) = param_2;
    return 0;
  }
  return 9;
}

