/* Address: 00023690; name: FUN_00023690; body bytes: 16 */

uint FUN_00023690(int param_1,uint param_2)

{
  if ((param_2 & param_2 - 1) != 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return (param_1 + param_2) - 1 & ~(param_2 - 1);
}

