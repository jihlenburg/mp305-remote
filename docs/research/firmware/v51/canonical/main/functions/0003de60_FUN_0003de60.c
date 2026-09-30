/* Address: 0003de60; name: FUN_0003de60; body bytes: 54 */

undefined4 FUN_0003de60(int *param_1,undefined4 param_2)

{
  if (*param_1 != 0) {
    if (param_1[1] == param_1[2]) {
      FUN_0003ded6(param_1,param_1[2] + 4);
    }
    FUN_0004a404(param_1[1] * param_1[3] + *param_1,param_2);
    param_1[1] = param_1[1] + 1;
    return 1;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

