/* Address: 00036de0; name: FUN_00036de0; body bytes: 160 */

float FUN_00036de0(int param_1)

{
  uint uVar1;
  uint in_fpscr;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  fVar2 = (float)VectorSignedToFloat(*(undefined4 *)(param_1 + 0x2c),(byte)(in_fpscr >> 0x16) & 3);
  if ((*(uint *)(param_1 + 0x4c) & 6) == 0) {
    fVar5 = *(float *)(param_1 + 0x34);
  }
  else {
    uVar1 = (*(uint *)(param_1 + 0x4c) & 7) >> 1;
    if (uVar1 != 2) {
      if (uVar1 == 1) {
        fVar5 = *(float *)(param_1 + 0x3c);
        if (fVar5 < *(float *)(param_1 + 0x38)) {
          fVar5 = fVar5 + 360.0;
        }
        fVar3 = *(float *)(param_1 + 0x34);
        fVar6 = *(float *)(param_1 + 0x30);
        fVar4 = fVar3;
        if (fVar3 < fVar6) {
          fVar4 = fVar3 + 360.0;
        }
        fVar5 = (float)VectorSignedToFloat((int)(*(float *)(param_1 + 0x38) + fVar5) / 2,
                                           (byte)((in_fpscr & 0xfffffff) >> 0x16) & 3);
        if (fVar5 <= fVar6) {
          if (fVar5 < fVar4) {
            return fVar3 + fVar2;
          }
          return fVar2 + fVar5;
        }
        fVar2 = fVar6 + fVar2;
      }
      return fVar2;
    }
    fVar5 = *(float *)(param_1 + 0x30);
  }
  return fVar5 + fVar2;
}

