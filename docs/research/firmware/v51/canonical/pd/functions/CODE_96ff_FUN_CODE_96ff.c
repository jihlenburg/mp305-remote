/* Address: CODE:96ff; name: FUN_CODE_96ff; body bytes: 26 */

char FUN_CODE_96ff(void)

{
  undefined1 *puVar1;
  
  if (DAT_INTMEM_b3 == '\x01') {
    puVar1 = &DAT_EXTMEM_072f;
  }
  else {
    if (DAT_INTMEM_b3 != '\0') {
      return DAT_INTMEM_b3;
    }
    puVar1 = &DAT_EXTMEM_072d;
  }
  return puVar1[1];
}

