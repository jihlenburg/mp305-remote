/* Address: ram:0004a9a4; name: FUN_ram_0004a9a4; body bytes: 176 */

int FUN_ram_0004a9a4(int param_1,undefined2 *param_2,undefined1 *param_3)

{
  int iVar1;
  code *pcVar2;
  undefined1 uVar3;
  undefined2 uStack_12;
  
  gp = 0x20004000;
  iVar1 = GATT_FindHandle(*(undefined2 *)(param_1 + 8),&uStack_12);
  if (iVar1 == 0) {
    iVar1 = 1;
    goto LAB_ram_0004aa30;
  }
  if ((*(byte *)(iVar1 + 8) & 0x20) != 0) {
    pcVar2 = (code *)FUN_ram_0004a174(uStack_12);
    if (pcVar2 == (code *)0x0) {
      iVar1 = 0xe;
      goto LAB_ram_0004aa30;
    }
    iVar1 = (*pcVar2)(*(undefined2 *)(param_1 + 2),iVar1,0x12);
    if (iVar1 != 0) goto LAB_ram_0004aa30;
  }
  uVar3 = 0x52;
  if (*(char *)(param_1 + 0x11) == '\0') {
    uVar3 = *(undefined1 *)(param_1 + 4);
  }
  iVar1 = FUN_ram_0004a6d0(*(undefined2 *)(param_1 + 2),*(undefined2 *)(param_1 + 8),
                           *(undefined4 *)(param_1 + 0xc),*(undefined2 *)(param_1 + 10),0,uVar3);
  if (iVar1 == 0) {
    if (*(char *)(param_1 + 0x11) != '\0') {
      gp = 0x20004000;
      return 0;
    }
    iVar1 = FUN_ram_00043d96(*(undefined2 *)(param_1 + 2));
    if (iVar1 == 0) {
      gp = 0x20004000;
      return 0;
    }
    gp = 0x20004000;
    return 0x16;
  }
  if (iVar1 == 0x16) {
    *param_3 = 0;
    gp = 0x20004000;
    return 0;
  }
LAB_ram_0004aa30:
  *param_2 = *(undefined2 *)(param_1 + 8);
  if (*(char *)(param_1 + 0x11) != '\0') {
    return 0;
  }
  gp = 0x20004000;
  return iVar1;
}

