/* Address: 0001897c; name: FUN_0001897c; body bytes: 40 */

uint FUN_0001897c(uint param_1,uint param_2,uint param_3,int param_4)

{
  return (param_2 / 100 & 0xff) << 0x10 | param_1 & 7 | (param_3 / 100 & 0x1ff) << 7 |
         param_4 << 0x18;
}

