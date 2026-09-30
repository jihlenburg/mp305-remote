/* Address: 0003f194; name: FUN_0003f194; body bytes: 20 */

void FUN_0003f194(int *param_1,int param_2,int param_3)

{
  if (param_1 == (int *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_2 != 0) {
    *param_1 = param_2;
    param_1[1] = 0;
    param_1[2] = param_3;
    *(undefined1 *)(param_1 + 3) = 0;
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

