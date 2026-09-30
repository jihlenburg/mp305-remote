/* Address: 0003de0e; name: FUN_0003de0e; body bytes: 24 */

int FUN_0003de0e(int *param_1,uint param_2)

{
  if ((uint)param_1[1] <= param_2) {
    return 0;
  }
  if (*param_1 != 0) {
    return param_2 * param_1[3] + *param_1;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

