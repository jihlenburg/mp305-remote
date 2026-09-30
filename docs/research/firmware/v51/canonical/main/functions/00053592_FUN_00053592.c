/* Address: 00053592; name: FUN_00053592; body bytes: 30 */

uint FUN_00053592(uint param_1,uint param_2)

{
  if (param_2 < 0xfd) {
    if (2 < param_2) {
      return ((int)(short)param_1 * (int)(short)param_2 * 0x8081 & 0x7fffffffU) >> 0x17;
    }
    param_1 = 0;
  }
  return param_1;
}

