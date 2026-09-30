/* Address: CODE:9f59; name: FUN_CODE_9f59; body bytes: 16 */

void FUN_CODE_9f59(void)

{
  char *pcVar1;
  
  pcVar1 = (char *)CONCAT11('\x03' - (((0xc9 < DAT_INTMEM_b3) << 7) >> 7),DAT_INTMEM_b3 + 0x36);
  *pcVar1 = *pcVar1 + '\x01';
  return;
}

