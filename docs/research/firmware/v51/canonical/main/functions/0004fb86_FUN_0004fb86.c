/* Address: 0004fb86; name: FUN_0004fb86; body bytes: 40 */

void FUN_0004fb86(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_0004a162(param_1 + 0x2c);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1[5] = 0xff;
    puVar1[6] = 0xff;
    puVar1[7] = 0;
    puVar1[8] = 0;
    puVar1[9] = 0;
    puVar1[10] = 0;
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

