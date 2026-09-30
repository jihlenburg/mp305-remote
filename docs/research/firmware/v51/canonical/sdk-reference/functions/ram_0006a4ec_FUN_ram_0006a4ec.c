/* Address: ram:0006a4ec; name: FUN_ram_0006a4ec; body bytes: 822 */

undefined4 FUN_ram_0006a4ec(int param_1)

{
  undefined1 uVar1;
  undefined2 uVar2;
  int iVar3;
  undefined1 *puVar4;
  uint uVar5;
  undefined1 uVar6;
  undefined4 uVar7;
  char cVar8;
  code *pcVar9;
  undefined4 *puVar10;
  undefined1 auStack_20 [12];
  ushort uStack_14;
  
  gp = 0x20004000;
  switch(*(char *)(param_1 + 2) + -6) {
  case '\0':
    FUN_ram_00069882(*(undefined2 *)(param_1 + 4));
    DAT_ram_200019ca = DAT_ram_200019ca & 0x7f;
    break;
  case '\x03':
    uVar5 = FUN_ram_00069942(*(undefined1 *)(param_1 + 3),param_1 + 4,0);
    if (uVar5 < DAT_ram_20001a8d) {
      FUN_ram_00042e5e(uVar5 * 6 + 0x25 & 0xff,4,param_1 + 0xc);
      FUN_ram_00042e10(DAT_ram_200019c4);
    }
    break;
  case '\x04':
    if ((*(char *)(param_1 + 1) == '\0') && ((*(byte *)(param_1 + 6) & 1) != 0)) {
      cVar8 = '\0';
      if (DAT_ram_20001aa8 == 0) {
        tmos_memset(auStack_20,0,0x10);
        if (*(int *)(param_1 + 0x14) == 0) {
          iVar3 = FUN_ram_0004df14(*(undefined2 *)(param_1 + 4));
          if (iVar3 == 0) {
            gp = 0x20004000;
            return 1;
          }
          iVar3 = iVar3 + 6;
        }
        else {
          iVar3 = *(int *)(param_1 + 0x14) + 0x10;
        }
        tmos_memcpy(auStack_20,iVar3,6);
        uStack_14 = (ushort)((int)(uint)*(byte *)(param_1 + 6) >> 2) & 1 | uStack_14;
        uVar5 = FUN_ram_00068a86();
        if (DAT_ram_20001a8d == uVar5) {
          if (DAT_ram_200019c8 != '\0') {
            FUN_ram_0006969c();
          }
          if (DAT_ram_20001bec != (code *)0x0) {
            (*DAT_ram_20001bec)(8,1);
          }
        }
        uVar5 = FUN_ram_00068a86();
        if (DAT_ram_20001a8d == uVar5) {
          DAT_ram_20001f0f = DAT_ram_20001f0f | 1;
        }
        else {
          DAT_ram_20001f0f = DAT_ram_20001f0f & 0xfe;
        }
        iVar3 = FUN_ram_000690dc(auStack_20,param_1);
        cVar8 = '\x15';
        if (iVar3 == 0) {
          tmos_set_event(DAT_ram_20001a8e,2);
          gp = 0x20004000;
          return 0;
        }
      }
    }
    else {
      cVar8 = '\0';
    }
    FUN_ram_00069302(*(undefined2 *)(param_1 + 4),1,*(undefined1 *)(param_1 + 1));
    if (cVar8 == '\0') {
      gp = 0x20004000;
      return 1;
    }
    uVar7 = 3;
    goto LAB_ram_0006a6ce;
  case '\x05':
    uVar2 = *(undefined2 *)(param_1 + 10);
    uVar6 = *(undefined1 *)(param_1 + 0xc);
    uVar1 = *(undefined1 *)(param_1 + 0xd);
    iVar3 = FUN_ram_0004df14(uVar2);
    if (iVar3 == 0) {
      gp = 0x20004000;
      return 1;
    }
    if (*(char *)(iVar3 + 0xc) == '\b') {
      uVar7 = DAT_ram_20001a94;
      if (DAT_ram_20001aac != (undefined4 *)0x0) {
        pcVar9 = (code *)*DAT_ram_20001aac;
joined_r0x0006a582:
        if (pcVar9 != (code *)0x0) {
          (*pcVar9)(param_1 + 3);
          gp = 0x20004000;
          return 1;
        }
      }
    }
    else {
      uVar7 = DAT_ram_20001a9c;
      if (DAT_ram_20001ab0 != (undefined4 *)0x0) {
        pcVar9 = (code *)*DAT_ram_20001ab0;
        goto joined_r0x0006a582;
      }
    }
    iVar3 = FUN_ram_00044c74(uVar7,uVar2,uVar6,uVar1);
    if (iVar3 == 0) {
      gp = 0x20004000;
      return 1;
    }
    uVar6 = 1;
    goto LAB_ram_0006a56e;
  case '\x06':
    FUN_ram_00069a36(*(undefined2 *)(param_1 + 4));
    break;
  case '\b':
    if ((*(char *)(param_1 + 1) == '\x06') &&
       (puVar4 = (undefined1 *)FUN_ram_0004df14(*(undefined2 *)(param_1 + 4)),
       puVar4 != (undefined1 *)0x0)) {
      if (DAT_ram_200019c6 != '\x02') {
        if (DAT_ram_200019c6 != '\x03') {
          if (DAT_ram_200019c6 == '\x01') {
            FUN_ram_00068f1c(*(undefined2 *)(param_1 + 4),puVar4[5],0);
          }
          goto LAB_ram_0006a716;
        }
        GAPBondMgr_SetParameter(0x410,0,0);
      }
      FUN_ram_00045118(*puVar4,*(undefined2 *)(param_1 + 4),5);
    }
LAB_ram_0006a716:
    cVar8 = *(char *)(param_1 + 1);
    uVar7 = 2;
LAB_ram_0006a6ce:
    FUN_ram_00069302(*(undefined2 *)(param_1 + 4),uVar7,cVar8);
    break;
  case '\t':
    uVar2 = *(undefined2 *)(param_1 + 4);
    uVar6 = DAT_ram_200019c5;
    if (DAT_ram_20001a8f == '\0') {
      if (DAT_ram_200019ca == 0) {
        uVar6 = 5;
      }
      else {
        iVar3 = FUN_ram_0004df14(uVar2);
        if (iVar3 == 0) {
          gp = 0x20004000;
          return 1;
        }
        if (((((*(byte *)(param_1 + 10) & 1) == 0) || (*(byte *)(iVar3 + 5) < 2)) ||
            ((*(ushort *)(param_1 + 0xc) & 0x200) != 0)) ||
           (uVar5 = FUN_ram_00069942(*(byte *)(iVar3 + 5),iVar3 + 6,auStack_20),
           DAT_ram_20001a8d != uVar5)) {
          FUN_ram_00068f1c(*(undefined2 *)(param_1 + 4),*(undefined1 *)(iVar3 + 5),param_1 + 8);
          cVar8 = '\0';
          uVar7 = 0;
          goto LAB_ram_0006a6ce;
        }
        uVar2 = *(undefined2 *)(param_1 + 4);
        uVar6 = 3;
      }
    }
LAB_ram_0006a56e:
    FUN_ram_000450ea(uVar2,uVar6);
    break;
  case '\x14':
    uVar2 = *(undefined2 *)(param_1 + 10);
    iVar3 = FUN_ram_0004df14(uVar2);
    if (iVar3 != 0) {
      puVar10 = DAT_ram_20001ab0;
      if (*(char *)(iVar3 + 0xc) == '\b') {
        puVar10 = DAT_ram_20001aac;
      }
      if ((puVar10 != (undefined4 *)0x0) && (puVar10[1] != 0)) {
        (*(code *)puVar10[2])
                  (param_1 + 3,uVar2,param_1 + 0xc,param_1 + 0x1c,puVar10[1],(code *)puVar10[2]);
      }
    }
  }
  return 1;
}

