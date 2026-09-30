/* Address: CODE:96e5; name: FUN_CODE_96e5; body bytes: 26 */

void FUN_CODE_96e5(void)

{
  if (DAT_INTMEM_b2 == '\b') {
    if (DAT_INTMEM_b4 == '\x06') {
      FUN_CODE_54bf();
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (DAT_INTMEM_b4 == '\a') {
      FUN_CODE_59c0();
      return;
    }
  }
  return;
}

