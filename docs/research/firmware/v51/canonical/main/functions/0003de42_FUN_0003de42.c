/* Address: 0003de42; name: FUN_0003de42; body bytes: 30 */

void FUN_0003de42(int *param_1,int param_2,int param_3)

{
  int iVar1;
  
  param_1[1] = 0;
  param_1[2] = param_2;
  param_1[3] = param_3;
  iVar1 = FUN_0004a318(param_2 * param_3);
  *param_1 = iVar1;
  if (iVar1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return;
}

