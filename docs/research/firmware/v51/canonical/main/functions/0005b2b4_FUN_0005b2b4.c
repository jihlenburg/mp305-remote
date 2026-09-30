/* Address: 0005b2b4; name: FUN_0005b2b4; body bytes: 198 */

float FUN_0005b2b4(float param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint in_fpscr;
  uint uVar3;
  
  uVar3 = (uint)param_1;
  if (((uVar3 & 0x7fffffff) >> 0x1d == 1) && ((int)(uVar3 & 0x9fffffff) < 0x1fffffff)) {
    if ((int)(uVar3 & 0x9fffffff) < 0x10000000) {
      uVar1 = uVar3 & 0x9fffffff;
    }
    else {
      uVar1 = 0xfffffff - (uVar3 & 0x9fffffff);
    }
    iVar2 = param_2;
    if ((int)(param_2 * uVar1) / 100 < param_2) {
      uVar1 = uVar3 & 0x9fffffff;
      if (0xfffffff < (int)(uVar3 & 0x9fffffff)) {
        uVar1 = 0xfffffff - uVar1;
      }
      iVar2 = (int)(param_2 * uVar1) / 100;
    }
    if (iVar2 < 0) {
      param_2 = 0;
    }
    else {
      uVar1 = uVar3 & 0x9fffffff;
      if (0xfffffff < (int)(uVar3 & 0x9fffffff)) {
        uVar1 = 0xfffffff - uVar1;
      }
      if ((int)(param_2 * uVar1) / 100 < param_2) {
        if ((int)(uVar3 & 0x9fffffff) < 0x10000000) {
          uVar3 = uVar3 & 0x9fffffff;
        }
        else {
          uVar3 = 0xfffffff - (uVar3 & 0x9fffffff);
        }
        param_2 = (int)(param_2 * uVar3) / 100;
      }
    }
    param_1 = (float)VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
  }
  return param_1;
}

