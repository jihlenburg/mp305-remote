/* Address: 00028036; name: FUN_00028036; body bytes: 10 */

/* Recovered from stored Thumb pointer at 0007a514; callback identification is inferred until
   reviewed. */

void FUN_00028036(int *param_1)

{
  if (param_1 != (int *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0002803c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*param_1 + 0x1c))();
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

