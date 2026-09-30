/* Address: ram:0005d0ca; name: FUN_ram_0005d0ca; body bytes: 390 */

undefined4 FUN_ram_0005d0ca(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined1 uVar9;
  undefined1 auStack_28 [8];
  undefined1 auStack_20 [8];
  undefined1 auStack_18 [8];
  
  gp = 0x20004000;
  iVar7 = FUN_ram_00057ba2();
  iVar8 = DAT_ram_20001de8;
  iVar6 = DAT_ram_20001dc0;
  if (iVar7 == 0) {
    gp = 0x20004000;
    return 2;
  }
  if (*(char *)(iVar7 + 0xb) == '\x01') {
    if (DAT_ram_20001dc0 == 0) {
      gp = 0x20004000;
      return 2;
    }
    if (((*(byte *)(DAT_ram_20001dc0 + 0x44) & 2) == 0) ||
       (*(char *)(*(int *)(DAT_ram_20001dc0 + 0x30) + 10) == '\0')) {
      tmos_memset(auStack_28,0,6);
    }
    else {
      tmos_memcpy(auStack_28,*(int *)(DAT_ram_20001dc0 + 0x30) + 0xc);
    }
    iVar8 = iVar6 + 0x46;
    if ((*(byte *)(iVar6 + 0x45) & 2) == 0) {
      tmos_memset(auStack_20,0,6);
    }
    else {
      tmos_memcpy(auStack_20,iVar8);
      iVar8 = *(int *)(iVar6 + 0x30) + 4;
    }
    tmos_memcpy(auStack_18,iVar8,6);
    uVar9 = *(undefined1 *)(iVar7 + 0x2f);
    uVar4 = *(undefined2 *)(iVar7 + 0x38);
    uVar1 = *(undefined1 *)(iVar6 + 0x45);
    uVar2 = *(undefined1 *)(iVar7 + 0xb);
    uVar5 = *(undefined2 *)(iVar7 + 8);
    uVar3 = *(undefined1 *)(iVar7 + 0x2a);
  }
  else {
    if (DAT_ram_20001de8 == 0) {
      gp = 0x20004000;
      return 2;
    }
    if ((*(byte *)(DAT_ram_20001de8 + 100) & 2) == 0) {
      tmos_memset(auStack_28,0,6);
    }
    else {
      tmos_memcpy(auStack_28,DAT_ram_20001de8 + 0x66);
    }
    if ((*(byte *)(iVar8 + 0x74) & 2) == 0) {
      tmos_memset(auStack_20,0,6);
      tmos_memcpy(auStack_18,iVar8 + 0x76,6);
    }
    else {
      tmos_memcpy(auStack_20,iVar8 + 0x76);
      tmos_memcpy(auStack_18,*(int *)(iVar8 + 0x84) + 4,6);
      *(byte *)(iVar8 + 0x75) = *(byte *)(*(int *)(iVar8 + 0x84) + 3) | 2;
    }
    uVar4 = *(undefined2 *)(iVar7 + 0x38);
    uVar1 = *(undefined1 *)(iVar8 + 0x75);
    uVar2 = *(undefined1 *)(iVar7 + 0xb);
    uVar5 = *(undefined2 *)(iVar7 + 8);
    uVar3 = *(undefined1 *)(iVar7 + 0x2a);
    uVar9 = 0;
  }
  FUN_ram_000682aa(uVar3,uVar5,uVar2,uVar1,auStack_18,auStack_28,auStack_20,uVar4,
                   *(undefined2 *)(iVar7 + 0x3a),*(undefined2 *)(iVar7 + 0x3c),uVar9);
  *(undefined1 *)(iVar7 + 0x2a) = 0;
  *(byte *)(iVar7 + 0xf) = *(byte *)(iVar7 + 0xf) | 1;
  return 0;
}

