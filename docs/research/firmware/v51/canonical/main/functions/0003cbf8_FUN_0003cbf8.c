/* Address: 0003cbf8; name: FUN_0003cbf8; body bytes: 174 */

undefined4 FUN_0003cbf8(float param_1,float param_2,int param_3)

{
  uint uVar1;
  float fVar2;
  
  for (fVar2 = *(float *)(param_3 + 0x3c) - *(float *)(param_3 + 0x38); fVar2 < 0.0;
      fVar2 = fVar2 + 360.0) {
  }
  for (; 0x43b3ffff < (int)fVar2; fVar2 = fVar2 - 360.0) {
  }
  if (fVar2 < param_1) {
    if (param_2 < 360.0 - fVar2) {
      if (param_2 < 360.0 - param_1) {
        if (fVar2 + param_2 < param_1) {
          return 0;
        }
        uVar1 = *(uint *)(param_3 + 0x4c) & 0xfffffff7;
      }
      else {
        uVar1 = *(uint *)(param_3 + 0x4c) | 8;
      }
      uVar1 = uVar1 & 0xffffffef;
      goto LAB_0003cc9e;
    }
    uVar1 = *(uint *)(param_3 + 0x4c) | 8;
  }
  else {
    if (fVar2 * 0.5 <= param_1) {
      uVar1 = *(uint *)(param_3 + 0x4c) & 0xfffffff7;
    }
    else {
      uVar1 = *(uint *)(param_3 + 0x4c) | 8;
    }
    *(uint *)(param_3 + 0x4c) = uVar1;
  }
  uVar1 = uVar1 | 0x10;
LAB_0003cc9e:
  *(uint *)(param_3 + 0x4c) = uVar1;
  return 1;
}

