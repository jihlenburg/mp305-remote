/* Address: 00040568; name: FUN_00040568; body bytes: 28 */

int FUN_00040568(uint param_1)

{
  return (param_1 >> 0x10 & 0xf8) * 0x100 + (param_1 >> 8 & 0xfc) * 8 + ((param_1 & 0xff) >> 3);
}

