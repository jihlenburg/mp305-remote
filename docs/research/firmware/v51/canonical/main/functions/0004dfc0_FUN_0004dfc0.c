/* Address: 0004dfc0; name: FUN_0004dfc0; body bytes: 52 */

bool FUN_0004dfc0(int param_1,undefined4 param_2)

{
  int iVar1;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (*(int *)(param_1 + 8) != 0) {
    iVar1 = *(int *)(param_1 + 8) + 8;
    if (iVar1 != 0) {
      FUN_0004669c();
      FUN_00046bec();
      iVar1 = FUN_0003de96(iVar1,param_2);
      return iVar1 != 0;
    }
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return false;
}

