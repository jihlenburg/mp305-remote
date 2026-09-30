/* Address: CODE:9d85; name: FUN_CODE_9d85; body bytes: 18 */

/* Inferred entry from 3 raw LCALL encodings. Review control flow before relying on semantics. */

char FUN_CODE_9d85(void)

{
  return (char)((ushort)DAT_INTMEM_b3 * 0x1c >> 8) -
         (((0x1b < (byte)((ushort)DAT_INTMEM_b3 * 0x1c)) << 7) >> 7);
}

