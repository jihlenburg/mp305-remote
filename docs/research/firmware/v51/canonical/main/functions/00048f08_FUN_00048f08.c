/* Address: 00048f08; name: FUN_00048f08; body bytes: 366 */

int FUN_00048f08(int param_1,int *param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint local_88;
  uint local_84;
  undefined1 *apuStack_80 [2];
  uint local_78;
  int local_74;
  uint local_70;
  undefined4 local_64;
  int local_5c [2];
  int local_54;
  undefined1 auStack_50 [16];
  int local_40;
  int local_38;
  int local_2c;
  
  if (param_2 == (int *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  local_40 = FUN_0004c924(param_1,0,0x12);
  local_40 = *param_2 - local_40;
  local_38 = FUN_0004c924(param_1,0,0x10);
  local_38 = param_2[1] - local_38;
  FUN_0004bab4(param_1,auStack_50);
  iVar7 = *(int *)(param_1 + 0x2c);
  local_64 = FUN_0003db28(auStack_50);
  local_2c = FUN_0003db0a(auStack_50);
  local_78 = FUN_0004cb34(param_1,0);
  local_54 = FUN_0004cb7c(param_1,0);
  local_70 = FUN_0004cb58(param_1,0);
  iVar1 = FUN_00046bd6(local_78);
  iVar8 = 0;
  uVar2 = FUN_000375a2(param_1);
  uVar6 = 0;
  while (uVar5 = uVar6, *(char *)(iVar7 + uVar6) != '\0') {
    if ((local_2c < local_54 + iVar8 + iVar1 + iVar1) && ((*(byte *)(param_1 + 0x5c) & 7) == 1)) {
      uVar2 = uVar2 | 4;
    }
    local_88 = 0;
    local_84 = uVar2;
    iVar4 = FUN_0005175c(iVar7 + uVar6,local_78,local_70,local_64);
    uVar5 = uVar6 + iVar4;
    if (local_38 <= iVar8 + iVar1) {
      local_88 = uVar5;
      iVar1 = FUN_00051d3c(iVar7,&local_88);
      if ((iVar1 != 10) && (*(char *)(iVar7 + uVar5) == '\0')) {
        uVar5 = uVar5 + 1;
      }
      break;
    }
    iVar8 = iVar8 + local_54 + iVar1;
    uVar6 = uVar5;
  }
  local_5c[0] = 0;
  iVar8 = iVar7 + uVar6;
  uVar3 = FUN_0004b108(param_1,0,*(undefined4 *)(param_1 + 0x2c));
  apuStack_80[0] = auStack_50;
  local_88 = local_78;
  local_84 = local_70;
  FUN_0002641a(local_5c,uVar3,iVar8,uVar5 - uVar6);
  local_74 = 0;
  iVar1 = local_74;
  if (uVar5 != 0) {
    while (iVar1 = local_74, local_74 + uVar6 < uVar5) {
      FUN_0005172c(iVar8,apuStack_80,&local_84,&local_74);
      iVar4 = FUN_00046b72(local_78,apuStack_80[0],local_84);
      if (((local_40 < iVar4 + local_5c[0]) || (local_74 + uVar6 == uVar5)) ||
         (*(char *)(iVar7 + iVar1 + uVar6) == '\0')) break;
      local_5c[0] = iVar4 + local_5c[0] + local_70;
    }
  }
  local_74 = iVar1;
  iVar1 = FUN_00051c60(iVar8,local_74);
  iVar7 = FUN_00051c60(iVar7,uVar6);
  return iVar7 + iVar1;
}

