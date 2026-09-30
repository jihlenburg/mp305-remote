/* Address: 0003f1b0; name: FUN_0003f1b0; body bytes: 34 */

void FUN_0003f1b0(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (*(int *)(param_1 + 4) != 0) {
    if (param_1 != 0) {
      iVar1 = *(int *)(param_1 + 4) + -1;
      *(int *)(param_1 + 4) = iVar1;
      if (iVar1 < 0) {
        *(undefined4 *)(param_1 + 4) = 0;
      }
      return;
    }
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return;
}

