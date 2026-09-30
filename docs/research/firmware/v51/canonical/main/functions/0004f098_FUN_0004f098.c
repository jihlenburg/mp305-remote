/* Address: 0004f098; name: FUN_0004f098; body bytes: 38 */

uint FUN_0004f098(uint param_1,int param_2)

{
  uint uVar1;
  
  if (((param_1 & 0x7fffffff) >> 0x1d == 1) &&
     (uVar1 = param_1 & 0x9fffffff, (int)uVar1 < 0x1fffffff)) {
    if (0xfffffff < (int)uVar1) {
      uVar1 = 0xfffffff - uVar1;
    }
    param_1 = (int)(param_2 * uVar1) / 100;
  }
  return param_1;
}

