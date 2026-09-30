/* Address: CODE:9a0d; name: FUN_CODE_9a0d; body bytes: 22 */

byte FUN_CODE_9a0d(byte param_1)

{
  undefined1 *puVar1;
  
  if (DAT_INTMEM_b3 == '\x01') {
    puVar1 = &DAT_EXTMEM_0633;
  }
  else {
    puVar1 = &DAT_EXTMEM_0631;
  }
  return puVar1[1] & param_1;
}

