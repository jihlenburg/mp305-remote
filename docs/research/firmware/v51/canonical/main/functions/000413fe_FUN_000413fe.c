/* Address: 000413fe; name: FUN_000413fe; body bytes: 44 */

void FUN_000413fe(uint *param_1)

{
  code *pcVar1;
  
  if (param_1 == (uint *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if ((int)((*param_1 >> 0x10) << 0x1b) < 0) {
    if (param_1[6] != 0) {
      pcVar1 = *(code **)(param_1[6] + 4);
      if (pcVar1 != (code *)0x0) {
        (*pcVar1)(param_1[5]);
      }
      FUN_00046bec(param_1);
      return;
    }
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return;
}

