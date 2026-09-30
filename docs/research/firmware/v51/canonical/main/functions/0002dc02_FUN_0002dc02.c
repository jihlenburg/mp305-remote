/* Address: 0002dc02; name: FUN_0002dc02; body bytes: 268 */

void FUN_0002dc02(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int local_138;
  int local_134;
  int local_130;
  int local_12c;
  undefined1 auStack_124 [120];
  undefined1 auStack_ac [124];
  undefined1 auStack_30 [20];
  
  iVar2 = FUN_00046698();
  uVar3 = FUN_00046718(param_1);
  FUN_0004bab4(iVar2,auStack_30);
  FUN_00042ec4(auStack_124);
  FUN_0004d0bc(iVar2,0x20000,auStack_124);
  FUN_00042a98(uVar3,auStack_124,auStack_30);
  iVar4 = FUN_0004bbec(iVar2);
  iVar5 = FUN_0003db28(iVar2 + 0x14);
  iVar5 = iVar5 - iVar4;
  if (*(int *)(iVar2 + 0x2c) == -1) {
    uVar7 = FUN_0004c584(iVar2);
    local_138 = iVar5;
    if ((uVar7 & 1) == 0) {
      local_138 = 0;
    }
  }
  else {
    iVar6 = iVar5 * *(int *)(iVar2 + 0x2c);
    local_138 = (int)(iVar6 + ((uint)(iVar6 >> 0x1f) >> 0x18)) >> 8;
  }
  cVar1 = FUN_0004c924(iVar2,0,0x27);
  if (cVar1 == '\x01') {
    local_138 = iVar5 - local_138;
  }
  local_134 = *(int *)(iVar2 + 0x18);
  local_12c = *(int *)(iVar2 + 0x20);
  local_138 = *(int *)(iVar2 + 0x14) + local_138;
  if (iVar4 < 1) {
    iVar4 = 0;
  }
  else {
    iVar4 = iVar4 + -1;
  }
  local_130 = local_138 + iVar4;
  iVar4 = FUN_0004c870(iVar2,0x30000);
  iVar5 = FUN_0004c8b2(iVar2,0x30000);
  iVar6 = FUN_0004c90c(iVar2,0x30000);
  iVar8 = FUN_0004c80a(iVar2,0x30000);
  local_138 = local_138 - iVar4;
  local_130 = local_130 + iVar5;
  local_134 = local_134 - iVar6;
  local_12c = local_12c + iVar8;
  FUN_00042ec4(auStack_ac);
  FUN_0004d0bc(iVar2,0x30000,auStack_ac);
  FUN_00042a98(uVar3,auStack_ac,&local_138);
  return;
}

