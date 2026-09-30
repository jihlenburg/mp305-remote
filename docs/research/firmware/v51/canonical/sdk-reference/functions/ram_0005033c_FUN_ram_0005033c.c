/* Address: ram:0005033c; name: FUN_ram_0005033c; body bytes: 588 */

undefined4 FUN_ram_0005033c(undefined2 *param_1)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  int iVar6;
  int iVar7;
  code *pcVar8;
  undefined1 uStack_98;
  undefined1 uStack_97;
  undefined1 uStack_96;
  undefined1 uStack_94;
  undefined1 uStack_93;
  undefined1 uStack_92;
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [72];
  
  gp = 0x20004000;
  iVar3 = FUN_ram_0004df14(*param_1);
  if (*(int *)(param_1 + 0x38) == 0) {
    uVar4 = FUN_ram_20000040(0x1c,0x53);
    *(undefined4 *)(param_1 + 0x38) = uVar4;
  }
  if (*(int *)(param_1 + 0x38) == 0) {
    gp = 0x20004000;
    return 0x13;
  }
  tmos_memset(*(int *)(param_1 + 0x38),0,0x1c);
  iVar6 = *(int *)(param_1 + 0x38);
  uVar2 = FUN_ram_0004e9a0(param_1);
  *(undefined1 *)(iVar6 + 0x1a) = uVar2;
  if (*(char *)(param_1 + 1) == '\0') {
    cVar1 = *(char *)(iVar3 + 5);
    iVar7 = *(int *)(param_1 + 0x40);
    pcVar8 = *(code **)(DAT_ram_20001f04 + 0x10);
    iVar6 = FUN_ram_000443b8();
    uVar4 = FUN_ram_00044398(0);
    (*pcVar8)(iVar7 + 0x20,param_1 + 0x2e,param_1 + 0x1e,cVar1 != '\0',iVar3 + 6,iVar6 != 0,uVar4,
              auStack_80,*(undefined4 *)(param_1 + 0x38));
    puVar5 = *(undefined1 **)(param_1 + 0x14);
    uStack_92 = puVar5[2];
    uStack_93 = puVar5[1];
    uStack_94 = *puVar5;
    pcVar8 = *(code **)(DAT_ram_20001f04 + 0x14);
    cVar1 = *(char *)(iVar3 + 5);
    iVar6 = FUN_ram_000443b8();
    uVar4 = FUN_ram_00044398(0);
    (*pcVar8)(auStack_80,param_1 + 0x2e,param_1 + 0x1e,param_1 + 4,&uStack_94,cVar1 != '\0',
              iVar3 + 6,iVar6 != 0,uVar4,auStack_90);
    iVar6 = tmos_memcmp(auStack_90,*(undefined4 *)(param_1 + 0x40),0x10);
    if (iVar6 == 0) {
      gp = 0x20004000;
      return 0xb;
    }
LAB_ram_00050466:
    puVar5 = *(undefined1 **)(param_1 + 0x36);
    uStack_96 = puVar5[0x12];
    uStack_97 = puVar5[1];
    uStack_98 = *puVar5;
    pcVar8 = *(code **)(DAT_ram_20001f04 + 0x14);
    iVar6 = FUN_ram_000443b8();
    uVar4 = FUN_ram_00044398(0);
    (*pcVar8)(auStack_80,param_1 + 0x1e,param_1 + 0x2e,param_1 + 0xc,&uStack_98,iVar6 != 0,uVar4,
              *(char *)(iVar3 + 5) != '\0',iVar3 + 6,auStack_70);
    uVar4 = FUN_ram_0004e78a(*param_1,0x11,auStack_70,&LAB_ram_000501ae);
  }
  else {
    if ((DAT_ram_20001f04 != 0) &&
       (pcVar8 = *(code **)(DAT_ram_20001f04 + 0x10), pcVar8 != (code *)0x0)) {
      iVar7 = *(int *)(param_1 + 0x40);
      iVar6 = FUN_ram_000443b8();
      uVar4 = FUN_ram_00044398(0);
      (*pcVar8)(iVar7 + 0x20,param_1 + 0x1e,param_1 + 0x2e,iVar6 != 0,uVar4,
                *(char *)(iVar3 + 5) != '\0',iVar3 + 6,auStack_80,*(undefined4 *)(param_1 + 0x38));
      puVar5 = *(undefined1 **)(param_1 + 0x14);
      uStack_92 = puVar5[2];
      uStack_93 = puVar5[1];
      uStack_94 = *puVar5;
      if ((DAT_ram_20001f04 != 0) &&
         (pcVar8 = *(code **)(DAT_ram_20001f04 + 0x14), pcVar8 != (code *)0x0)) {
        cVar1 = *(char *)(iVar3 + 5);
        iVar6 = FUN_ram_000443b8();
        uVar4 = FUN_ram_00044398(0);
        (*pcVar8)(auStack_80,param_1 + 0x2e,param_1 + 0x1e,param_1 + 4,&uStack_94,cVar1 != '\0',
                  iVar3 + 6,iVar6 != 0,uVar4,*(undefined4 *)(param_1 + 0x40));
        goto LAB_ram_00050466;
      }
    }
    uVar4 = 0xfe;
  }
  return uVar4;
}

