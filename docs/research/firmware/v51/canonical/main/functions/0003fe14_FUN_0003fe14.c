/* Address: 0003fe14; name: FUN_0003fe14; body bytes: 100 */

uint FUN_0003fe14(uint param_1,uint param_2,uint param_3,int param_4)

{
  uint uVar1;
  
  if (((param_2 & 0x7fffffff) >> 0x1d == 1) &&
     (uVar1 = param_2 & 0x9fffffff, (int)uVar1 < 0x1fffffff)) {
    if (0xfffffff < (int)uVar1) {
      uVar1 = 0xfffffff - uVar1;
    }
    param_2 = (int)(param_4 * uVar1) / 100;
  }
  if (((param_3 & 0x7fffffff) >> 0x1d == 1) &&
     (uVar1 = param_3 & 0x9fffffff, (int)uVar1 < 0x1fffffff)) {
    if (0xfffffff < (int)uVar1) {
      uVar1 = 0xfffffff - uVar1;
    }
    param_3 = (int)(param_4 * uVar1) / 100;
  }
  uVar1 = param_3;
  if ((int)param_1 < (int)param_3) {
    uVar1 = param_1;
  }
  if ((int)param_2 <= (int)uVar1) {
    if ((int)param_3 <= (int)param_1) {
      return param_3;
    }
    return param_1;
  }
  return param_2;
}

