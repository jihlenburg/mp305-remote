/* Address: 0003ded6; name: FUN_0003ded6; body bytes: 34 */

void FUN_0003ded6(int *param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = FUN_0004f588(*param_1,param_2 * param_1[3]);
  if (iVar1 != 0) {
    param_1[2] = param_2;
    *param_1 = iVar1;
    if (param_2 < (uint)param_1[1]) {
      param_1[1] = param_2;
    }
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

