/* Address: ram:0006a822; name: FUN_ram_0006a822; body bytes: 484 */

uint FUN_ram_0006a822(undefined4 param_1,uint param_2)

{
  char cVar1;
  undefined2 uVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  undefined4 uVar6;
  short sStack_24;
  undefined1 auStack_22 [10];
  
  gp = 0x20004000;
  if ((short)param_2 < 0) {
    pcVar4 = (char *)tmos_msg_receive(DAT_ram_20001a8e);
    if (pcVar4 != (char *)0x0) {
      cVar1 = *pcVar4;
      if (cVar1 == -0x4f) {
        if (pcVar4[4] == '\0') {
          DAT_ram_20001aa0 = '\0';
          FUN_ram_00069b54(*(undefined2 *)(pcVar4 + 2),*(undefined2 *)(pcVar4 + 6),
                           *(undefined2 *)(pcVar4 + 8));
          if (DAT_ram_20001aa0 != '\0') {
            DAT_ram_20001aa0 = '\0';
            FUN_ram_00042e10(DAT_ram_200019c4);
          }
        }
      }
      else if (cVar1 == -0x30) {
        iVar5 = FUN_ram_0006a4ec();
        if (iVar5 == 0) goto LAB_ram_0006a896;
      }
      else if (cVar1 == -0x50) {
        if (pcVar4[4] == '\x1e') {
          FUN_ram_00069ac0(*(undefined2 *)(pcVar4 + 2),0);
        }
        GATT_bm_free(pcVar4 + 8,pcVar4[4]);
      }
      tmos_msg_deallocate(pcVar4);
    }
LAB_ram_0006a896:
    return param_2 ^ 0x8000;
  }
  if ((param_2 & 2) != 0) {
    iVar5 = FUN_ram_000690dc(0,0);
    uVar3 = param_2 ^ 2;
    uVar6 = 1;
    if (iVar5 == 0) {
      uVar6 = 2;
    }
LAB_ram_0006a90a:
    tmos_set_event(DAT_ram_20001a8e,uVar6);
    gp = 0x20004000;
    return uVar3;
  }
  if ((param_2 & 1) == 0) {
    if ((param_2 & 4) == 0) {
      gp = 0x20004000;
      return 0;
    }
    gp = 0x20004000;
    return param_2 ^ 4;
  }
  uVar2 = *(undefined2 *)(DAT_ram_20001aa8 + 4);
  if (DAT_ram_20001aa4 == 0) {
    DAT_ram_20001aa4 = FUN_ram_0004aaf8(1,0xffff,&DAT_ram_0006c644,2,&DAT_ram_20001ab4);
  }
  if (DAT_ram_20001aa4 != 0) {
    iVar5 = FUN_ram_0004b062(uVar2,DAT_ram_20001aa4,DAT_ram_20001ab4,&sStack_24,auStack_22,0,2,0xff)
    ;
    if ((iVar5 == 0) && (sStack_24 != 0)) {
      FUN_ram_00069b54(uVar2,*(undefined2 *)(DAT_ram_20001aa4 + 10));
    }
    DAT_ram_20001aa4 = FUN_ram_0004afa0(DAT_ram_20001aa4,0xffff,DAT_ram_20001ab4,0);
    uVar3 = (param_2 ^ 1) & 0xffff;
    if (DAT_ram_20001aa4 != 0) {
      uVar6 = 1;
      goto LAB_ram_0006a90a;
    }
  }
  FUN_ram_00069302(*(undefined2 *)(DAT_ram_20001aa8 + 4),1,0);
  FUN_ram_00069302(*(undefined2 *)(DAT_ram_20001aa8 + 4),3,0);
  FUN_ram_00042e10(DAT_ram_200019c4);
  FUN_ram_00068ade();
  gp = 0x20004000;
  return (param_2 ^ 1) & 0xffff;
}

