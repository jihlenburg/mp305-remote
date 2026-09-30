/* Address: CODE:9767; name: FUN_CODE_9767; body bytes: 26 */

void FUN_CODE_9767(void)

{
  if (DAT_INTMEM_b2 == '\x03') {
    if (DAT_INTMEM_b4 == '\v') {
      return;
    }
    if (DAT_INTMEM_b4 == '\n') {
      return;
    }
  }
  return;
}

