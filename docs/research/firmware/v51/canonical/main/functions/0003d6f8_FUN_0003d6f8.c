/* Address: 0003d6f8; name: FUN_0003d6f8; body bytes: 182 */

void FUN_0003d6f8(float param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  if (0x43b40000 < (int)param_1) {
    param_1 = param_1 - 360.0;
  }
  fVar5 = *(float *)(param_2 + 0x30);
  fVar2 = *(float *)(param_2 + 0x34) - fVar5;
  fVar1 = *(float *)(param_2 + 0x34) - param_1;
  if (fVar2 < 0.0) {
    fVar2 = fVar2 + 360.0;
  }
  if (fVar1 < 0.0) {
    fVar1 = fVar1 + 360.0;
  }
  fVar4 = fVar1 - fVar2;
  if (fVar4 <= 0.0) {
    fVar4 = fVar2 - fVar1;
  }
  if ((int)fVar4 < 0x43340001) {
    fVar4 = fVar5;
    fVar3 = param_1;
    if ((fVar1 < fVar2) || (fVar4 = param_1, fVar3 = fVar5, fVar2 < fVar1)) {
      FUN_0003a970(fVar4,fVar3,param_2,0x20000);
    }
  }
  else {
    FUN_0004d3d8(param_2);
  }
  FUN_0003aa38(param_2);
  *(float *)(param_2 + 0x30) = param_1;
  FUN_0003aa38(param_2);
  return;
}

