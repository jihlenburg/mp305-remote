/* Address: 000402b8; name: FUN_000402b8; body bytes: 26 */

uint FUN_000402b8(uint param_1)

{
  return (((param_1 & 0xffff) >> 8) + ((param_1 & 0xffffff) >> 0x10) * 3 + (param_1 & 0xff) * 4 &
         0x7ff) >> 3;
}

