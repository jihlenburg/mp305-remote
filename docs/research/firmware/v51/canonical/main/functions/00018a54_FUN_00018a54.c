/* Address: 00018a54; name: FUN_00018a54; body bytes: 416 */

void FUN_00018a54(int param_1,uint param_2)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  
  uVar1 = (short)param_2 * 1000;
  uVar5 = uVar1 / 5 & 0xffff;
  uVar9 = uVar1 / 9 & 0xffff;
  uVar8 = uVar1 / 0xc & 0xffff;
  uVar7 = uVar1 / 0xf & 0xffff;
  uVar6 = uVar1 / 0x14 & 0xffff;
  uVar4 = uVar1 / 0x14 & 0xffff;
  local_34 = 1;
  local_38 = 1;
  local_3c = 1;
  local_40 = 1;
  local_44 = 2;
  local_48 = 3;
  local_4c = 4;
  local_50 = 5;
  uVar3 = uVar1 / 0x15 & 0xffff;
  uVar1 = uVar1 / 0xf & 0xffff;
  if (3000 < uVar5) {
    uVar5 = 3000;
  }
  if (3000 < uVar9) {
    uVar9 = 3000;
  }
  if (3000 < uVar8) {
    uVar8 = 3000;
  }
  if (3000 < uVar7) {
    uVar7 = 3000;
  }
  if (5000 < uVar6) {
    uVar6 = 5000;
  }
  if (5000 < uVar3) {
    uVar3 = 5000;
  }
  if (3000 < uVar1) {
    uVar1 = 3000;
  }
  if (5000 < uVar4) {
    uVar4 = 5000;
  }
  if ((3000 < uVar3) && (uVar6 < 0xdac)) {
    uVar3 = 3000;
  }
  if ((3000 < uVar4) && (uVar6 < 0xdac)) {
    uVar4 = 3000;
  }
  if (param_2 < 0x8c) {
    local_4c = 0;
    local_50 = 0;
    local_48 = 0;
  }
  if (param_2 < 0x25) {
    local_44 = 0;
    local_40 = 0;
    uVar4 = 0;
    local_3c = 0;
    if ((param_2 < 0x13) && (local_38 = 0, param_2 < 0xd)) {
      local_34 = 0;
    }
  }
  (&DAT_1fffa340)[param_1] = (char)param_2;
  FUN_0003bc70(&DAT_1fffa138 + param_1 * 0x10,&DAT_00018bf8,param_2);
  uVar2 = FUN_000189ce(1,5000,uVar5);
  param_1 = param_1 * 0x24;
  *(undefined4 *)(&DAT_1fffa1d8 + param_1) = uVar2;
  uVar2 = FUN_000189ce(local_34,9000,uVar9);
  *(undefined4 *)(&DAT_1fffa1dc + param_1) = uVar2;
  uVar2 = FUN_000189ce(local_38,12000,uVar8);
  *(undefined4 *)(&DAT_1fffa1e0 + param_1) = uVar2;
  uVar2 = FUN_000189ce(local_3c,15000,uVar7);
  *(undefined4 *)(&DAT_1fffa1e4 + param_1) = uVar2;
  uVar2 = FUN_000189ce(local_40,20000,uVar6);
  *(undefined4 *)(&DAT_1fffa1e8 + param_1) = uVar2;
  uVar2 = FUN_000189fa(local_44,0xce4,21000,uVar3);
  *(undefined4 *)(&DAT_1fffa1ec + param_1) = uVar2;
  uVar2 = FUN_000189a4(local_50,uVar1,uVar4);
  *(undefined4 *)(&DAT_1fffa1f0 + param_1) = uVar2;
  uVar2 = FUN_000189ce(local_48,28000,5000);
  *(undefined4 *)(&DAT_1fffa1f4 + param_1) = uVar2;
  uVar2 = FUN_0001897c(local_4c,15000,28000,0x8c);
  *(undefined4 *)(&DAT_1fffa1f8 + param_1) = uVar2;
  return;
}

