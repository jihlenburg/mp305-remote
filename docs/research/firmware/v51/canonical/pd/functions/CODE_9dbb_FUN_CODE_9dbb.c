/* Address: CODE:9dbb; name: FUN_CODE_9dbb; body bytes: 18 */

/* Inferred entry from 6 raw LCALL encodings. Review control flow before relying on semantics. */

char FUN_CODE_9dbb(void)

{
  return ((char)((ushort)DAT_INTMEM_b3 * 0x1a >> 8) -
         (((0xa7 < (byte)((ushort)DAT_INTMEM_b3 * 0x1a)) << 7) >> 7)) + '\x03';
}

