/* Address: 0003bc5a; name: FUN_0003bc5a; body bytes: 22 */

uint FUN_0003bc5a(uint param_1)

{
  return (param_1 & 0xf8) * 0x100 + (param_1 & 0xfc) * 8 + (param_1 >> 3) & 0xffff;
}

