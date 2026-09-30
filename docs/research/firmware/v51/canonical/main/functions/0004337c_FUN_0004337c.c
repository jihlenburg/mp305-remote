/* Address: 0004337c; name: FUN_0004337c; body bytes: 604 */

void FUN_0004337c(int param_1,undefined4 *param_2)

{
  byte bVar1;
  ushort uVar2;
  undefined3 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  int *piVar7;
  int iVar8;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  uint uStack_64;
  int local_60;
  int local_5c;
  undefined4 local_58;
  int local_54;
  undefined4 local_50;
  int local_4c;
  int iStack_48;
  int iStack_44;
  undefined4 uStack_40;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  int local_2c;
  int local_28;
  int iStack_24;
  undefined4 uStack_20;
  
  if (*(byte *)(param_2 + 5) < 3) {
    return;
  }
  if ((param_2[6] != 0) && (*(char *)(param_2 + 7) == '\0')) {
    return;
  }
  iVar4 = FUN_0003db4c(&local_2c,*param_2,*(undefined4 *)(param_1 + 8));
  if (iVar4 == 0) {
    return;
  }
  piVar7 = *(int **)(param_1 + 4);
  uVar2 = *(ushort *)(*piVar7 + 8);
  uStack_64 = (uint)uVar2;
  if (param_2[1] == 0) {
    local_6c = FUN_0003db28(&local_2c);
    local_68 = FUN_0003db0a(&local_2c);
    local_58 = CONCAT13(*(undefined1 *)(param_2 + 5),*(undefined3 *)((int)param_2 + 0x15));
    local_60 = param_2[6];
    if ((local_60 == 0) || (*(char *)(param_2 + 7) == '\x01')) {
      local_60 = 0;
    }
    local_54 = local_2c;
    local_50 = local_28;
    local_4c = iStack_24;
    iStack_48 = uStack_20;
    FUN_0003ddd6(&local_54,-piVar7[1],-piVar7[2]);
    local_70 = FUN_00042398(piVar7,local_2c - piVar7[1],local_28 - piVar7[2]);
    if (local_60 != 0) {
      local_5c = param_2[9];
      if (local_5c == 0) {
        local_5c = FUN_0003db28(param_2[8]);
      }
      local_60 = local_5c * (local_28 - ((int *)param_2[8])[1]) + local_60 +
                 (local_2c - *(int *)param_2[8]);
    }
    bVar1 = *(byte *)(piVar7 + 5);
    if (bVar1 == 0x10) {
      FUN_00043748(&local_70);
      return;
    }
    if (bVar1 < 0x11) {
      if (bVar1 == 6) {
        FUN_00043a86(&local_70);
        return;
      }
      if (bVar1 == 7) {
        FUN_000438b4(&local_70);
        return;
      }
      if (bVar1 != 0xf) {
        return;
      }
      uVar5 = 3;
    }
    else {
      if (bVar1 != 0x11) {
        if (bVar1 == 0x12) {
          FUN_00043ba0(&local_70);
          return;
        }
        if (bVar1 != 0x15) {
          return;
        }
        FUN_000435ea(&local_70);
        return;
      }
      uVar5 = 4;
    }
    FUN_00043d9c(&local_70,uVar5);
    return;
  }
  iVar4 = FUN_0003db4c(&local_2c,&local_2c,param_2[4]);
  if (iVar4 == 0) {
    return;
  }
  if ((param_2[8] != 0) && (iVar4 = FUN_0003db4c(&local_2c), iVar4 == 0)) {
    return;
  }
  local_6c = FUN_0003db28(&local_2c);
  local_68 = FUN_0003db0a(&local_2c);
  uVar3 = CONCAT21(local_50._2_2_,*(undefined1 *)(param_2 + 5));
  local_50._0_3_ = CONCAT12(*(undefined1 *)(param_2 + 10),(short)uVar3 << 8);
  local_54 = param_2[2];
  local_50 = CONCAT31(local_50._1_3_,*(undefined1 *)(param_2 + 3));
  iVar8 = param_2[1];
  iVar4 = FUN_00040314(*(undefined1 *)(param_2 + 3));
  local_58 = local_54 * (local_28 - ((int *)param_2[4])[1]) + iVar8 +
             ((uint)(iVar4 * (local_2c - *(int *)param_2[4])) >> 3);
  if ((param_2[6] == 0) || (*(char *)(param_2 + 7) == '\x01')) {
    local_60 = 0;
  }
  else {
    local_60 = param_2[6];
    local_5c = param_2[9];
    if (local_5c == 0) {
      local_5c = FUN_0003db28(param_2[8]);
    }
    local_60 = local_5c * (local_28 - ((int *)param_2[8])[1]) + local_60 +
               (local_2c - *(int *)param_2[8]);
  }
  local_4c = local_2c;
  iStack_48 = local_28;
  iStack_44 = iStack_24;
  uStack_40 = uStack_20;
  FUN_0003ddd6(&local_4c,-piVar7[1],-piVar7[2]);
  puVar6 = (undefined4 *)param_2[4];
  local_3c = *puVar6;
  uStack_38 = puVar6[1];
  uStack_34 = puVar6[2];
  uStack_30 = puVar6[3];
  FUN_0003ddd6(&local_3c,-piVar7[1],-piVar7[2]);
  local_70 = FUN_00042398(piVar7,local_2c - piVar7[1],local_28 - piVar7[2]);
  switch((char)piVar7[5]) {
  case '\x06':
    FUN_00043ffa(&local_70);
    break;
  case '\a':
    FUN_00043fb8(&local_70);
    break;
  case '\b':
  case '\t':
  case '\n':
  case '\v':
  case '\f':
  case '\r':
  case '\x0e':
  case '\x13':
    break;
  case '\x0f':
    uVar5 = 3;
    goto LAB_000435ca;
  case '\x10':
    FUN_00043f76(&local_70);
    break;
  case '\x11':
    uVar5 = 4;
LAB_000435ca:
    FUN_0004407e(&local_70,uVar5);
    break;
  case '\x12':
  case '\x14':
    FUN_0004403c(&local_70);
    break;
  case '\x15':
    FUN_00043f34(&local_70);
  }
  return;
}

