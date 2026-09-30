/* Address: 00044bbc; name: FUN_00044bbc; body bytes: 964 */

void FUN_00044bbc(int param_1,int param_2,int *param_3)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  undefined2 *puVar11;
  byte bVar12;
  int iVar13;
  int iVar14;
  int *local_d8;
  int local_d4;
  undefined1 local_cc;
  int *local_c8;
  undefined1 local_c4;
  undefined2 local_c3;
  undefined1 local_c1;
  int local_c0;
  undefined1 local_bc;
  int *local_b8;
  int local_a4;
  uint local_a0;
  int local_9c;
  int local_98;
  int local_94;
  int local_90;
  int local_8c;
  int local_88;
  undefined4 local_84;
  int local_80;
  int local_7c;
  int local_78;
  undefined4 local_74;
  int local_70;
  undefined1 *local_6c;
  undefined4 local_68;
  undefined1 auStack_60 [36];
  int local_3c;
  int local_30;
  int iStack_2c;
  int *piStack_28;
  
  if (*(byte *)(param_2 + 0x20) < 3) {
    return;
  }
  local_9c = *param_3;
  local_98 = param_3[1];
  local_94 = param_3[2];
  local_90 = param_3[3];
  local_30 = param_1;
  iStack_2c = param_2;
  piStack_28 = param_3;
  iVar4 = FUN_0003db4c(&local_7c,&local_9c,*(undefined4 *)(param_1 + 8));
  if (iVar4 == 0) {
    return;
  }
  bVar1 = *(byte *)(param_2 + 0x2f);
  bVar12 = bVar1 & 7;
  if ((bVar1 & 7) == 0) {
    uVar5 = (uint)*(uint3 *)(param_2 + 0x21);
  }
  else {
    uVar5 = *(uint *)(param_2 + 0x24);
  }
  FUN_0001049c(&local_d8,0x2c);
  local_c3 = (undefined2)uVar5;
  local_c1 = (undefined1)(uVar5 >> 0x10);
  if (*(int *)(param_2 + 0x1c) == 0 && (bVar1 & 7) == 0) {
    local_d8 = &local_9c;
    local_c4 = *(undefined1 *)(param_2 + 0x20);
    FUN_0004337c(local_30,&local_d8);
    return;
  }
  local_a0 = (uint)*(byte *)(param_2 + 0x20);
  if (0xfc < local_a0) {
    local_a0 = 0xff;
  }
  iVar6 = FUN_0003db28(&local_9c);
  iVar7 = FUN_0003db0a(&local_9c);
  iVar4 = iVar6;
  if (iVar7 <= iVar6) {
    iVar4 = iVar7;
  }
  iVar13 = *(int *)(param_2 + 0x1c);
  if (iVar4 >> 1 <= *(int *)(param_2 + 0x1c)) {
    iVar13 = iVar4 >> 1;
  }
  iVar4 = FUN_0003db28(&local_7c);
  iVar14 = 0;
  local_6c = (undefined1 *)0x0;
  local_68 = 0;
  if (0 < iVar13) {
    iVar14 = FUN_0004a318(iVar4);
    FUN_000454e8(auStack_60,&local_9c,iVar13,0);
    local_6c = auStack_60;
  }
  local_8c = local_7c;
  local_84 = local_74;
  local_d8 = &local_8c;
  local_c4 = 0xff;
  local_c0 = iVar14;
  local_b8 = local_d8;
  piVar8 = (int *)FUN_000470ce(param_2 + 0x24,iVar6,iVar7);
  iVar6 = 0;
  bVar2 = false;
  if ((piVar8 != (int *)0x0) && (1 < bVar12)) {
    local_c8 = &local_8c;
    local_d4 = *piVar8 + local_9c * -3 + local_7c * 3;
    for (uVar5 = 0; uVar5 < *(byte *)(param_2 + 0x2e); uVar5 = uVar5 + 1) {
      if (*(char *)(uVar5 * 5 + param_2 + 0x27) != -1) {
        bVar2 = true;
        break;
      }
    }
    if ((bVar12 == 2) && (bVar2)) {
      iVar6 = (piVar8[1] + local_7c) - local_9c;
    }
    local_cc = 0xf;
  }
  for (iVar7 = 0; iVar7 < iVar13; iVar7 = iVar7 + 1) {
    iVar9 = local_98 + iVar7;
    local_a4 = local_90 - iVar7;
    if ((local_78 <= iVar9) || (local_a4 <= local_70)) {
      local_3c = 0;
      FUN_0004a57a(iVar14,local_a0,iVar4);
      iVar10 = FUN_000452b4(&local_6c,iVar14,local_8c,iVar9,iVar4);
      local_bc = (undefined1)iVar10;
      if (iVar10 == 1) {
        local_bc = 2;
      }
      bVar3 = false;
      if (local_78 <= iVar9) {
        if (bVar12 == 1) {
          puVar11 = (undefined2 *)(*piVar8 + (iVar9 - local_98) * 3);
          local_c3 = *puVar11;
          local_c1 = *(undefined1 *)(puVar11 + 1);
          local_c4 = *(undefined1 *)(piVar8[1] + (iVar9 - local_98));
        }
        else if ((bVar12 == 2) && (bVar3 = true, iVar6 != 0)) {
          local_3c = 1;
          for (iVar10 = 0; iVar10 < iVar4; iVar10 = iVar10 + 1) {
            if (*(byte *)(iVar6 + iVar10) < 0xfd) {
              *(char *)(iVar14 + iVar10) =
                   (char)((uint)((int)(short)(ushort)*(byte *)(iVar14 + iVar10) *
                                (int)(short)(ushort)*(byte *)(iVar6 + iVar10)) >> 8);
            }
          }
          local_bc = 2;
        }
        local_88 = iVar9;
        local_80 = iVar9;
        FUN_0004337c(local_30,&local_d8);
      }
      if (local_a4 <= local_70) {
        local_88 = local_a4;
        local_80 = local_a4;
        iVar10 = local_3c;
        if (bVar12 == 1) {
          puVar11 = (undefined2 *)(*piVar8 + (local_a4 - local_98) * 3);
          local_c3 = *puVar11;
          local_c1 = *(undefined1 *)(puVar11 + 1);
          local_c4 = *(undefined1 *)(piVar8[1] + (local_a4 - local_98));
joined_r0x00044e3e:
          if (iVar10 != 0) {
            if (2 < bVar12) {
              FUN_0004a57a(iVar14,local_a0,iVar4);
              FUN_000452b4(&local_6c,iVar14,local_8c,iVar9,iVar4);
            }
            for (iVar9 = 0; iVar9 < iVar4; iVar9 = iVar9 + 1) {
              if (*(byte *)(iVar6 + iVar9) < 0xfd) {
                *(char *)(iVar14 + iVar9) =
                     (char)((uint)((int)(short)(ushort)*(byte *)(iVar14 + iVar9) *
                                  (int)(short)(ushort)*(byte *)(iVar6 + iVar9)) >> 8);
              }
            }
            local_bc = 2;
          }
        }
        else if ((bVar12 != 2) || (iVar10 = iVar6, !bVar3)) goto joined_r0x00044e3e;
        FUN_0004337c(local_30,&local_d8);
      }
    }
  }
  local_c4 = (undefined1)local_a0;
  if ((bVar1 & 7) == 0) {
    local_88 = local_98 + iVar13;
    local_80 = local_90 - iVar13;
    local_c0 = 0;
    FUN_0004337c(local_30,&local_d8);
    goto LAB_00044f6a;
  }
  switch(bVar12) {
  case 1:
    local_bc = 1;
    break;
  case 2:
switchD_00044ebe_caseD_2:
    local_bc = 2;
    local_c0 = iVar6;
    break;
  case 3:
  case 4:
  case 5:
    if (bVar2) goto switchD_00044ebe_caseD_2;
    local_bc = 1;
    local_c0 = iVar6;
  }
  iVar4 = local_98 + iVar13;
  if (local_98 + iVar13 <= local_78) {
    iVar4 = local_78;
  }
  iVar6 = local_90 - iVar13;
  if (local_70 <= local_90 - iVar13) {
    iVar6 = local_70;
  }
  for (; iVar4 <= iVar6; iVar4 = iVar4 + 1) {
    if (bVar12 == 1) {
      iVar7 = iVar4 - local_98;
      puVar11 = (undefined2 *)(*piVar8 + iVar7 * 3);
      local_c3 = *puVar11;
      local_c1 = *(undefined1 *)(puVar11 + 1);
      if (local_a0 < 0xfd) {
        local_c4 = (undefined1)
                   ((uint)((int)(short)(ushort)*(byte *)(piVar8[1] + iVar7) * (int)(short)local_a0)
                   >> 8);
      }
      else {
        local_c4 = *(undefined1 *)(piVar8[1] + iVar7);
      }
    }
    local_88 = iVar4;
    local_80 = iVar4;
    FUN_0004337c(local_30,&local_d8);
  }
LAB_00044f6a:
  if (iVar14 != 0) {
    FUN_00046bec();
    FUN_00045330(auStack_60);
  }
  if (piVar8 != (int *)0x0) {
    thunk_FUN_00046bec();
  }
  return;
}

