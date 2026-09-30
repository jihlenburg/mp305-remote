/* Address: ram:00050910; name: FUN_ram_00050910; body bytes: 436 */

undefined4 FUN_ram_00050910(uint param_1,undefined4 param_2,uint param_3)

{
  ushort *puVar1;
  int iVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [24];
  
  gp = 0x20004000;
  puVar3 = auStack_40;
  iVar2 = FUN_ram_0004df14();
  puVar1 = *(ushort **)(iVar2 + 0x34);
  tmos_memset(auStack_40,0,0x10);
  if ((puVar1 != (ushort *)0x0) && (uVar6 = (uint)*puVar1, uVar6 == param_1)) {
    if (*(char *)((int)puVar1 + 3) == '!') {
      if (*(int *)(puVar1 + 0x40) == 0) {
        iVar2 = FUN_ram_00051502(puVar1 + 4,puVar1 + 0x1e,puVar1 + 0x2e,auStack_40);
        if (iVar2 == 0) goto LAB_ram_0005095a;
      }
      else {
        puVar3 = *(undefined1 **)(puVar1 + 0x38);
        if (puVar3 != (undefined1 *)0x0) goto LAB_ram_0005095a;
      }
    }
    else {
      iVar2 = *(int *)(puVar1 + 0x38);
      if (((iVar2 != 0) && (*(ushort *)(iVar2 + 0x10) == param_3)) &&
         (iVar2 = tmos_memcmp(param_2,iVar2 + 0x12,8), iVar2 != 0)) {
        puVar3 = *(undefined1 **)(puVar1 + 0x38);
        goto LAB_ram_0005095a;
      }
    }
  }
  iVar2 = FUN_ram_0004df14(param_1);
  if (iVar2 == 0) {
    gp = 0x20004000;
    return 1;
  }
  iVar4 = *(int *)(iVar2 + 0x2c);
  uVar6 = param_1;
  if (((iVar4 != 0) && (*(ushort *)(iVar4 + 0x10) == param_3)) &&
     (iVar4 = tmos_memcmp(param_2,iVar4 + 0x12,8), iVar4 == 1)) {
    if ((DAT_ram_200019cb == '\0') ||
       (puVar3 = *(undefined1 **)(iVar2 + 0x2c), (*(undefined1 **)(iVar2 + 0x2c))[0x1b] == '\x01'))
    {
      thunk_FUN_ram_00065e24(param_1,0xf);
      if (DAT_ram_20001bec != (code *)0x0) {
        (*DAT_ram_20001bec)(7,2);
        gp = 0x20004000;
        return 0;
      }
      gp = 0x20004000;
      return 0;
    }
LAB_ram_0005095a:
    thunk_FUN_ram_0006535a(uVar6,puVar3);
    return 1;
  }
  if ((((DAT_ram_20001f10 & 1) != 0) && (*(char *)(iVar2 + 5) == DAT_ram_20001f08)) &&
     (iVar2 = tmos_memcmp(iVar2 + 6,&DAT_ram_20001f09,6), iVar2 == 1)) {
    if (DAT_ram_20001bec != (code *)0x0) {
      (*DAT_ram_20001bec)(7,4);
    }
    thunk_FUN_ram_00065e24(param_1,0xf);
    gp = 0x20004000;
    return 1;
  }
  if (DAT_ram_20001f0f == '\0') {
    uVar5 = 1;
    if (DAT_ram_20001bec == (code *)0x0) goto LAB_ram_00050a7c;
  }
  else {
    if ((DAT_ram_20001f10 & 2) == 0) {
      if (DAT_ram_20001bec != (code *)0x0) {
        (*DAT_ram_20001bec)(7,3);
      }
      tmos_memset(auStack_30,0,0x10);
      tmos_memcpy(auStack_30,&DAT_ram_20001c1c,6);
      LL_Encrypt(auStack_30,auStack_30,auStack_40);
      puVar3 = auStack_40;
      goto LAB_ram_0005095a;
    }
    if (DAT_ram_20001bec == (code *)0x0) goto LAB_ram_00050a7c;
    uVar5 = 5;
  }
  (*DAT_ram_20001bec)(7,uVar5);
LAB_ram_00050a7c:
  thunk_FUN_ram_0006538a(param_1);
  gp = 0x20004000;
  return 1;
}

