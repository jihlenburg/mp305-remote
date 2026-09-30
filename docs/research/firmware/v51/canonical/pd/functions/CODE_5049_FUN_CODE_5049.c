/* Address: CODE:5049; name: FUN_CODE_5049; body bytes: 21 */

/* Inferred entry from 3 raw LCALL encodings. Review control flow before relying on semantics. */

byte FUN_CODE_5049(void)

{
  return *(byte *)(CONCAT11(DAT_EXTMEM_04b4,DAT_EXTMEM_04b5) + 1) & 0xf;
}

