/* Address: 000423a0; name: FUN_000423a0; body bytes: 194 */

undefined8 FUN_000423a0(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  local_18 = *(int *)(param_2 + 0x30);
  local_20 = param_1;
  local_1c = param_2;
  if ((local_18 != 0) && (2 < *(byte *)(param_2 + 0x3c))) {
    fVar4 = *(float *)(param_2 + 0x1c);
    fVar3 = *(float *)(param_2 + 0x24);
    fVar5 = fVar3;
    if (fVar4 < fVar3) {
      fVar5 = fVar4;
    }
    local_20 = (int)fVar5 - local_18;
    if (fVar3 < fVar4) {
      fVar3 = fVar4;
    }
    local_18 = local_18 + (int)fVar3;
    fVar3 = *(float *)(param_2 + 0x28);
    if (*(float *)(param_2 + 0x20) < *(float *)(param_2 + 0x28)) {
      fVar3 = *(float *)(param_2 + 0x20);
    }
    local_1c = (int)fVar3 - *(int *)(param_2 + 0x30);
    fVar3 = *(float *)(param_2 + 0x28);
    if (*(float *)(param_2 + 0x28) < *(float *)(param_2 + 0x20)) {
      fVar3 = *(float *)(param_2 + 0x20);
    }
    local_14 = (int)fVar3 + *(int *)(param_2 + 0x30);
    iVar1 = FUN_00040c36(param_1,&local_20);
    uVar2 = FUN_0004a318(0x40);
    *(undefined4 *)(iVar1 + 0x4c) = uVar2;
    FUN_0004a404(uVar2,param_2,0x40);
    *(undefined1 *)(iVar1 + 4) = 7;
    FUN_0004197c(param_1,iVar1);
  }
  return CONCAT44(local_1c,local_20);
}

