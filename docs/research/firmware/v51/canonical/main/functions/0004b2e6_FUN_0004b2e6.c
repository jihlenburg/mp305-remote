/* Address: 0004b2e6; name: FUN_0004b2e6; body bytes: 40 */

void FUN_0004b2e6(undefined4 param_1,int *param_2)

{
  int *piVar1;
  
  piVar1 = (int *)*param_2;
  if (*piVar1 != 0) {
    *param_2 = *piVar1;
    FUN_0004b2e6(param_1);
    *param_2 = (int)piVar1;
  }
  if ((code *)piVar1[1] != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0004b30a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*(code *)piVar1[1])(param_1,param_2);
    return;
  }
  return;
}

