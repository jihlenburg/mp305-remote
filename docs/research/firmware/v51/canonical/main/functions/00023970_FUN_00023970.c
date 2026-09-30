/* Address: 00023970; name: FUN_00023970; body bytes: 32 */

void FUN_00023970(undefined4 *param_1,undefined4 param_2)

{
  if (param_1[1] != 0) {
    FUN_00023970();
  }
  if ((code *)*param_1 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0002398c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*(code *)*param_1)(param_1,param_2);
    return;
  }
  return;
}

