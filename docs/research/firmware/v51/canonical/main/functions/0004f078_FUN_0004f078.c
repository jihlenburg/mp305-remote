/* Address: 0004f078; name: FUN_0004f078; body bytes: 32 */

uint FUN_0004f078(uint param_1)

{
  if ((int)param_1 < 0) {
    if ((int)param_1 < -0xffffffe) {
      param_1 = 0xf0000001;
    }
    param_1 = 0xfffffff - param_1;
  }
  else if (0xffffffe < (int)param_1) {
    param_1 = 0xfffffff;
  }
  return param_1 | 0x20000000;
}

