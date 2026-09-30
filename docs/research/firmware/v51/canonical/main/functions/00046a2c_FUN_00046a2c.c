/* Address: 00046a2c; name: FUN_00046a2c; body bytes: 10 */

void FUN_00046a2c(int *param_1)

{
  if (*param_1 != 0) {
                    /* WARNING: Could not recover jumptable at 0x00046a32. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 4))();
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

