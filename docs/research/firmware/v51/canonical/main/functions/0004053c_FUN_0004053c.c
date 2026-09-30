/* Address: 0004053c; name: FUN_0004053c; body bytes: 24 */

uint FUN_0004053c(uint param_1,int param_2)

{
  return (param_1 >> 0x10 & 0xff) << 0x10 | (param_1 >> 8 & 0xff) << 8 | param_1 & 0xff |
         param_2 << 0x18;
}

