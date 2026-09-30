/* Address: 00052ac6; name: FUN_00052ac6; body bytes: 8 */

void FUN_00052ac6(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x10) = param_2;
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

