/* Address: CODE:9b27; name: FUN_CODE_9b27; body bytes: 21 */

char FUN_CODE_9b27(byte param_1)

{
  FUN_CODE_a99c(4);
  return ((char)((ushort)param_1 * 4 >> 8) - ((((char)((ushort)param_1 * 4) != '\0') << 7) >> 7)) +
         -0x4f;
}

