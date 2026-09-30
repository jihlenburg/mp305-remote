/* Address: 0004925c; name: FUN_0004925c; body bytes: 370 */

undefined4 FUN_0004925c(int param_1,int *param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint local_74 [4];
  undefined4 local_64;
  undefined4 local_5c [2];
  undefined4 local_54;
  int local_50;
  undefined1 auStack_4c [20];
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int *piStack_28;
  
  if (param_2 == (int *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  local_2c = param_1;
  piStack_28 = param_2;
  FUN_0004bab4(param_1,auStack_4c);
  iVar9 = *(int *)(local_2c + 0x2c);
  local_38 = local_2c;
  local_64 = FUN_0003db28(auStack_4c);
  local_30 = FUN_0003db0a(auStack_4c);
  uVar1 = FUN_0004cb34(local_2c,0);
  local_50 = FUN_0004cb7c(local_2c,0);
  iVar2 = FUN_0004cb58(local_2c,0);
  iVar3 = FUN_00046bd6(uVar1);
  uVar4 = FUN_000375a2(local_38);
  iVar8 = 0;
  uVar7 = 0;
  while (uVar6 = uVar7, *(char *)(iVar9 + uVar7) != '\0') {
    local_34 = iVar8 + iVar3;
    if ((local_30 < local_50 + local_34 + iVar3) && ((*(byte *)(local_38 + 0x5c) & 7) == 1)) {
      uVar4 = uVar4 | 4;
    }
    iVar5 = FUN_0005175c(iVar9 + uVar7,uVar1,iVar2,local_64,0,uVar4);
    uVar6 = uVar7 + iVar5;
    if (param_2[1] <= local_34) break;
    iVar8 = iVar8 + local_50 + iVar3;
    uVar7 = uVar6;
  }
  iVar8 = FUN_0004b108(local_2c,0,*(undefined4 *)(local_38 + 0x2c));
  iVar3 = 0;
  if (iVar8 == 2) {
    iVar3 = FUN_00051a28(iVar9 + uVar7,uVar6 - uVar7,uVar1,iVar2);
    iVar8 = FUN_0003db28(auStack_4c);
    iVar3 = iVar8 / 2 - iVar3 / 2;
  }
  else if (iVar8 == 3) {
    iVar8 = FUN_00051a28(iVar9 + uVar7,uVar6 - uVar7,uVar1,iVar2);
    iVar3 = FUN_0003db28(auStack_4c);
    iVar3 = iVar3 - iVar8;
  }
  local_5c[0] = 0;
  local_54 = 0;
  iVar8 = 0;
  if (uVar6 != 0) {
    local_74[0] = uVar7;
    while (uVar7 = local_74[0], local_74[0] <= uVar6 - 1) {
      FUN_0005172c(iVar9,local_5c,&local_54,local_74);
      iVar5 = FUN_00046b72(uVar1,local_5c[0],local_54);
      iVar8 = iVar3;
      if (*param_2 < iVar5 + iVar3) break;
      iVar3 = iVar5 + iVar3 + iVar2;
    }
  }
  local_74[0] = uVar7;
  iVar3 = FUN_00046b72(uVar1,local_5c[0],local_54);
  if ((*param_2 < iVar8 - iVar2) || (iVar3 + iVar2 + 1 + iVar8 < *param_2)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

