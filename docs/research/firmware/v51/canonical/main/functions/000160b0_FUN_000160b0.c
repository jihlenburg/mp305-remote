/* Address: 000160b0; name: FUN_000160b0; body bytes: 24 */

undefined1 FUN_000160b0(int param_1)

{
  undefined1 *puVar1;
  
  if (DAT_1fff8f48 <= DAT_1fff8f54) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  puVar1 = (undefined1 *)(param_1 + DAT_1fff8f54);
  DAT_1fff8f54 = DAT_1fff8f54 + 1;
  return *puVar1;
}

