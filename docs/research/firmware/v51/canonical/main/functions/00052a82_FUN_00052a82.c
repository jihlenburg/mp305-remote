/* Address: 00052a82; name: FUN_00052a82; body bytes: 22 */

void FUN_00052a82(int *param_1)

{
  int iVar1;
  
  if (param_1 != (int *)0x0) {
    iVar1 = FUN_00052708();
    param_1[1] = (iVar1 - *param_1) + -1;
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

