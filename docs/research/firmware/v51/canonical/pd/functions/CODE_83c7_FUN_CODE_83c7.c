/* Address: CODE:83c7; name: FUN_CODE_83c7; body bytes: 13 */

/* Inferred entry from 4 raw LCALL encodings. Review control flow before relying on semantics. */

char FUN_CODE_83c7(void)

{
  char in_PSW;
  
  return DAT_EXTMEM_06ed - (in_PSW >> 7);
}

