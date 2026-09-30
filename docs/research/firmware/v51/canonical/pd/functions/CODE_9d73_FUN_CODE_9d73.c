/* Address: CODE:9d73; name: FUN_CODE_9d73; body bytes: 18 */

char FUN_CODE_9d73(void)

{
  return ((char)((ushort)DAT_INTMEM_b3 * 10 >> 8) -
         (((0xc6 < (byte)((ushort)DAT_INTMEM_b3 * 10)) << 7) >> 7)) + '\x06';
}

