/* Address: CODE:9f19; name: FUN_CODE_9f19; body bytes: 16 */

/* Inferred entry from 8 raw LCALL encodings. Review control flow before relying on semantics. */

void FUN_CODE_9f19(void)

{
  char *pcVar1;
  
  pcVar1 = (char *)CONCAT11('\x03' - (((0xbf < DAT_INTMEM_b3) << 7) >> 7),DAT_INTMEM_b3 + 0x40);
  *pcVar1 = *pcVar1 + '\x01';
  return;
}

