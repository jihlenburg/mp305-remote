/* Address: CODE:1de3; name: FUN_CODE_1de3; body bytes: 14 */

/* Inferred entry from 4 raw LCALL encodings. Review control flow before relying on semantics. */

char FUN_CODE_1de3(char param_1)

{
  return '\x03' - (((0xcU < (byte)(param_1 * '\x04')) << 7) >> 7);
}

