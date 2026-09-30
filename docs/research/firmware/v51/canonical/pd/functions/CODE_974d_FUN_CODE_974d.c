/* Address: CODE:974d; name: FUN_CODE_974d; body bytes: 26 */

/* Inferred entry from 17 raw LCALL encodings. Review control flow before relying on semantics. */

char FUN_CODE_974d(byte param_1,char param_2,byte param_3)

{
  FUN_CODE_33d6();
  return (char)((ushort)param_3 * 4 >> 8) +
         ((param_2 - (((0xcb < param_1) << 7) >> 7)) -
         ((CARRY1((byte)((ushort)param_3 * 4),param_1 + 0x34) << 7) >> 7));
}

