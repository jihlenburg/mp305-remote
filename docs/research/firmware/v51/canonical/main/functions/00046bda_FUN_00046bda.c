/* Address: 00046bda; name: FUN_00046bda; body bytes: 18 */

void FUN_00046bda(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if ((iVar1 != 0) && (*(code **)(iVar1 + 8) != (code *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x00046be8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(iVar1 + 8))(iVar1,param_1);
    return;
  }
  return;
}

