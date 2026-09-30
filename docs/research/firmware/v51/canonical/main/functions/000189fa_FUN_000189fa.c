/* Address: 000189fa; name: FUN_000189fa; body bytes: 46 */

uint FUN_000189fa(uint param_1,uint param_2,uint param_3,uint param_4)

{
  return param_2 / 100 << 0x18 | (param_3 / 100 & 0xff) << 0x10 |
         param_1 & 7 | (param_4 / 0x32 & 0x7f) << 9;
}

