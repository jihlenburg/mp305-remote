/* Address: CODE:9bf3; name: FUN_CODE_9bf3; body bytes: 20 */

char FUN_CODE_9bf3(void)

{
  return *(char *)CONCAT11('\x06' - (((0x30U < (byte)(DAT_INTMEM_b3 * '\x19')) << 7) >> 7),
                           DAT_INTMEM_b3 * '\x19' - 0x31) + -1;
}

