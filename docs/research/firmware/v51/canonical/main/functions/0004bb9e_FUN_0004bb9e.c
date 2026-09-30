/* Address: 0004bb9e; name: FUN_0004bb9e; body bytes: 18 */

void FUN_0004bb9e(int param_1)

{
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (*(int *)(param_1 + 8) != 0) {
    FUN_0004669c(*(int *)(param_1 + 8) + 8);
    return;
  }
  return;
}

