/* Address: 00031a78; name: FUN_00031a78; body bytes: 496 */

void FUN_00031a78(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  undefined1 auStack_100 [8];
  int local_f8;
  uint uStack_f4;
  int local_e4;
  undefined1 local_e0;
  undefined2 local_df;
  undefined1 local_dd;
  byte local_d1;
  int local_88;
  undefined4 uStack_84;
  int local_80;
  undefined4 uStack_7c;
  int local_74;
  int local_68;
  undefined4 local_64;
  int local_60;
  undefined4 local_5c;
  undefined4 uStack_58;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_3c;
  int local_38;
  
  iVar1 = FUN_0003db4c(&local_88,param_1 + 0x14,param_2 + 0x18);
  if (iVar1 != 0) {
    local_64 = *(undefined4 *)(param_2 + 0x18);
    local_5c = *(undefined4 *)(param_2 + 0x1c);
    uStack_58 = *(undefined4 *)(param_2 + 0x20);
    uVar2 = *(undefined4 *)(param_2 + 0x24);
    *(int *)(param_2 + 0x18) = local_88;
    *(undefined4 *)(param_2 + 0x1c) = uStack_84;
    *(int *)(param_2 + 0x20) = local_80;
    *(undefined4 *)(param_2 + 0x24) = uStack_7c;
    iVar1 = FUN_0004c858(param_1,0);
    iVar3 = FUN_0004c8f4(param_1,0);
    local_68 = FUN_0004bb1a(param_1);
    local_74 = FUN_0004baf8(param_1);
    local_60 = param_1 + 0x2c;
    uVar4 = FUN_0004a120();
    iVar5 = FUN_0004c828(param_1,0);
    uVar10 = ((1 - *(uint *)(param_1 + 0x70)) * iVar5 + local_68) / *(uint *)(param_1 + 0x70);
    iVar5 = FUN_0004c828(param_1,&LAB_00050000);
    uVar4 = ((1 - uVar4) * iVar5 + uVar10) / uVar4;
    if ((int)uVar4 < 1) {
      uVar4 = 1;
    }
    iVar6 = FUN_0004c696(param_1,0);
    iVar7 = FUN_0004bd90(param_1);
    local_38 = (iVar1 - iVar7) + iVar6;
    iVar1 = FUN_0004bf14(param_1);
    local_3c = (iVar3 - iVar1) + iVar6;
    FUN_00042ec4(auStack_100);
    FUN_0004d0bc(param_1,&LAB_00050000,auStack_100);
    local_d1 = local_d1 & 0xf8;
    local_e0 = 0xff;
    local_44 = *(int *)(param_1 + 0x20) + local_e4;
    for (uVar9 = 0; uVar9 < *(uint *)(param_1 + 0x70); uVar9 = uVar9 + 1) {
      iVar1 = local_38 + (uVar9 * (local_68 - uVar10)) / (*(uint *)(param_1 + 0x70) - 1);
      iVar6 = *(int *)(param_1 + 0x14);
      local_f8 = 0;
      uStack_f4 = uVar9;
      iVar3 = FUN_0004a118(local_60);
      iVar1 = iVar1 + iVar6;
      while (iVar3 != 0) {
        iVar6 = iVar1;
        if ((*(byte *)(iVar3 + 0x10) & 1) == 0) {
          if ((int)((uint)*(byte *)(param_1 + 0x74) << 0x1c) < 0) {
            iVar7 = 0;
          }
          else {
            iVar7 = *(int *)(iVar3 + 0xc);
          }
          local_48 = (uVar4 - 1) + iVar1;
          iVar6 = uVar4 + iVar5 + iVar1;
          local_50 = iVar1;
          if (local_88 <= local_48) {
            if (local_80 < iVar1) break;
            local_df = *(undefined2 *)(iVar3 + 8);
            local_dd = *(undefined1 *)(iVar3 + 10);
            iVar7 = (iVar7 + uVar9) -
                    *(uint *)(param_1 + 0x70) * ((iVar7 + uVar9) / *(uint *)(param_1 + 0x70));
            iVar8 = param_1 + ((int)((uint)*(byte *)(iVar3 + 0x10) << 0x1b) >> 0x1f) * -4;
            iVar1 = *(int *)(iVar8 + 0x44);
            local_4c = local_3c +
                       (local_74 -
                       ((*(int *)(*(int *)(iVar3 + 4) + iVar7 * 4) - iVar1) * local_74) /
                       (*(int *)(iVar8 + 0x4c) - iVar1)) + *(int *)(param_1 + 0x18);
            if (*(int *)(*(int *)(iVar3 + 4) + iVar7 * 4) != 0x7fffffff) {
              FUN_00042a98(param_2,auStack_100,&local_50);
            }
          }
          local_f8 = local_f8 + 1;
        }
        iVar3 = FUN_0004a13c(local_60,iVar3);
        iVar1 = iVar6;
      }
    }
    *(undefined4 *)(param_2 + 0x18) = local_64;
    *(undefined4 *)(param_2 + 0x1c) = local_5c;
    *(undefined4 *)(param_2 + 0x20) = uStack_58;
    *(undefined4 *)(param_2 + 0x24) = uVar2;
  }
  return;
}

