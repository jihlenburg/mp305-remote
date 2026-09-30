/* Address: 00045006; name: FUN_00045006; body bytes: 508 */

void FUN_00045006(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined1 auStack_68 [28];
  undefined4 local_4c;
  undefined1 local_48;
  undefined2 local_47;
  undefined1 local_45;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  
  if ((*(int *)(param_2 + 0x30) != 0) && (2 < *(byte *)(param_2 + 0x3c))) {
    fVar4 = *(float *)(param_2 + 0x1c);
    fVar3 = *(float *)(param_2 + 0x24);
    if ((fVar4 != fVar3) || (*(float *)(param_2 + 0x20) != *(float *)(param_2 + 0x28))) {
      fVar5 = fVar3;
      if (fVar4 < fVar3) {
        fVar5 = fVar4;
      }
      local_20 = *(int *)(param_2 + 0x30) / 2;
      local_28 = (int)fVar5 - local_20;
      if (fVar3 < fVar4) {
        fVar3 = fVar4;
      }
      local_20 = (int)fVar3 + local_20;
      fVar3 = *(float *)(param_2 + 0x28);
      if (*(float *)(param_2 + 0x20) < *(float *)(param_2 + 0x28)) {
        fVar3 = *(float *)(param_2 + 0x20);
      }
      local_24 = (int)fVar3 - *(int *)(param_2 + 0x30) / 2;
      fVar3 = *(float *)(param_2 + 0x28);
      if (*(float *)(param_2 + 0x28) < *(float *)(param_2 + 0x20)) {
        fVar3 = *(float *)(param_2 + 0x20);
      }
      local_1c = (int)fVar3 + *(int *)(param_2 + 0x30) / 2;
      iVar1 = FUN_0003db4c(&local_28,&local_28,*(undefined4 *)(param_1 + 8));
      if (iVar1 != 0) {
        if (*(float *)(param_2 + 0x20) == *(float *)(param_2 + 0x28)) {
          FUN_0002cd3c(param_1,param_2);
        }
        else if (*(float *)(param_2 + 0x1c) == *(float *)(param_2 + 0x24)) {
          FUN_0002d188();
        }
        else {
          FUN_0002ce94(param_1,param_2);
        }
        if (((int)((uint)*(byte *)(param_2 + 0x3d) << 0x1c) < 0) ||
           ((int)((uint)*(byte *)(param_2 + 0x3d) << 0x1d) < 0)) {
          FUN_00041964(auStack_68);
          local_47 = *(undefined2 *)(param_2 + 0x2c);
          local_45 = *(undefined1 *)(param_2 + 0x2e);
          local_4c = 0x7fff;
          local_48 = *(undefined1 *)(param_2 + 0x3c);
          iVar1 = *(int *)(param_2 + 0x30) >> 1;
          iVar2 = ((*(int *)(param_2 + 0x30) << 0x1f) >> 0x1f) + 1;
          if ((int)((uint)*(byte *)(param_2 + 0x3d) << 0x1d) < 0) {
            local_38 = (int)*(float *)(param_2 + 0x1c) - iVar1;
            local_34 = (int)*(float *)(param_2 + 0x20) - iVar1;
            local_30 = ((int)*(float *)(param_2 + 0x1c) + iVar1) - iVar2;
            local_2c = ((int)*(float *)(param_2 + 0x20) + iVar1) - iVar2;
            FUN_00044bbc(param_1,auStack_68,&local_38);
          }
          if ((int)((uint)*(byte *)(param_2 + 0x3d) << 0x1c) < 0) {
            local_38 = (int)*(float *)(param_2 + 0x24) - iVar1;
            local_34 = (int)*(float *)(param_2 + 0x28) - iVar1;
            local_30 = ((int)*(float *)(param_2 + 0x24) + iVar1) - iVar2;
            local_2c = ((int)*(float *)(param_2 + 0x28) + iVar1) - iVar2;
            FUN_00044bbc(param_1,auStack_68,&local_38);
          }
        }
      }
    }
  }
  return;
}

