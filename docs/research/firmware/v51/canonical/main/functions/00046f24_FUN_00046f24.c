/* Address: 00046f24; name: FUN_00046f24; body bytes: 24 */

void FUN_00046f24(uint *param_1,byte *param_2,uint param_3)

{
  byte *pbVar1;
  
  pbVar1 = param_2;
  if ((*param_2 != 0) && (pbVar1 = param_2 + 1, *pbVar1 == 0x3a)) {
    pbVar1 = param_2 + 2;
  }
  *param_1 = param_3 & 0xffffff00 | (uint)*param_2;
  param_1[1] = (uint)pbVar1;
  return;
}

