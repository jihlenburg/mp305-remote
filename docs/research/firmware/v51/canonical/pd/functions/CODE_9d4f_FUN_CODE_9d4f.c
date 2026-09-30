/* Address: CODE:9d4f; name: FUN_CODE_9d4f; body bytes: 18 */

void FUN_CODE_9d4f(void)

{
  undefined1 *puVar1;
  
  if (DAT_INTMEM_b9 == '\x01') {
    puVar1 = &DAT_EXTMEM_05e6;
  }
  else {
    puVar1 = &DAT_EXTMEM_05e2;
  }
  *puVar1 = 1;
  return;
}

