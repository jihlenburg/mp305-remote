/* Address: 000248e8; name: FUN_000248e8; body bytes: 76 */

void FUN_000248e8(byte *param_1,uint param_2,int param_3,undefined4 param_4)

{
  uint uVar1;
  
  uVar1 = param_2 & 0xff;
  if (param_3 == 1) {
    uVar1 = uVar1 + *param_1;
    if (0xfe < uVar1) {
      uVar1 = 0xff;
    }
  }
  else if (param_3 == 2) {
    uVar1 = *param_1 - uVar1;
    if ((int)uVar1 < 1) {
      uVar1 = 0;
    }
  }
  else {
    if (param_3 != 3) {
      return;
    }
    uVar1 = (uint)((int)(short)(ushort)*param_1 * (int)(short)uVar1) >> 8;
  }
  FUN_0003ff88((uint)param_1 & 0xffff0000 | uVar1 & 0xff | (param_2 >> 8 & 0xff) << 8,param_1,
               param_4);
  return;
}

