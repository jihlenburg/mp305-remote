/* Address: CODE:9e49; name: FUN_CODE_9e49; body bytes: 16 */

void FUN_CODE_9e49(void)

{
  char *pcVar1;
  
  pcVar1 = (char *)CONCAT11('\a' - (((0xb4 < DAT_INTMEM_b3) << 7) >> 7),DAT_INTMEM_b3 + 0x4b);
  *pcVar1 = *pcVar1 + '\x01';
  return;
}

