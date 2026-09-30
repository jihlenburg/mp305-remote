/* Address: ram:00049af8; name: FUN_ram_00049af8; body bytes: 494 */

int FUN_ram_00049af8(undefined4 param_1,short *param_2,undefined1 *param_3)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  ushort auStack_38 [2];
  int iStack_34;
  
  gp = 0x20004000;
  if (*param_2 != 0) {
    gp = 0x20004000;
    return 6;
  }
  cVar1 = (char)param_2[1];
  if ((cVar1 - 0x1bU & 0xfd) == 0) {
    if (DAT_ram_20001a38 == -1) {
      gp = 0x20004000;
      return 6;
    }
    if (cVar1 == '\x1d') {
      iVar3 = FUN_ram_00049522();
      if ((iVar3 != 0) && (*(char *)(iVar3 + 10) != '\0')) {
        if (*(char *)(iVar3 + 10) < '\0') {
          gp = 0x20004000;
          return 0;
        }
        FUN_ram_00048828(param_1,0x1d);
        *(byte *)(iVar3 + 10) = *(byte *)(iVar3 + 10) | 0x80;
        gp = 0x20004000;
        return 0;
      }
    }
    else {
      iVar3 = 0;
    }
    iVar4 = FUN_ram_000438f4((char)*param_2,*(undefined1 *)((int)param_2 + 1),
                             *(undefined4 *)(param_2 + 4),param_2[2],auStack_38);
    if (iVar4 != 0) {
      gp = 0x20004000;
      return iVar4;
    }
    iVar4 = FUN_ram_000487a4(DAT_ram_20001a38,param_1,0,(char)param_2[1],auStack_38);
    if (iVar4 == 0) {
      if (iStack_34 != 0) {
        *param_3 = 0;
      }
      if (((char)param_2[1] == '\x1d') && (iVar3 != 0)) {
        *(undefined1 *)(iVar3 + 10) = 0x1d;
        gp = 0x20004000;
        return 0;
      }
      return 0;
    }
    gp = 0x20004000;
    return iVar4;
  }
  iVar3 = FUN_ram_00049522();
  if (iVar3 == 0) {
    gp = 0x20004000;
    return 0;
  }
  if (cVar1 == '\x01') {
    iVar4 = FUN_ram_000432ce(*(undefined4 *)(param_2 + 4),param_2[2],auStack_38);
  }
  else {
    if (*(char *)(iVar3 + 2) != cVar1) {
      gp = 0x20004000;
      return 4;
    }
    if (*(code **)(iVar3 + 4) == (code *)0x0) {
      gp = 0x20004000;
      return 4;
    }
    iVar4 = (**(code **)(iVar3 + 4))(*(undefined4 *)(param_2 + 4),param_2[2],auStack_38);
  }
  if (iVar4 != 0) {
    gp = 0x20004000;
    return iVar4;
  }
  uVar8 = (uint)*(byte *)(iVar3 + 2);
  if (uVar8 < 0x12) {
    uVar8 = 0x222a0U >> (uVar8 & 0x1f) & 1;
LAB_ram_00049ca6:
    if (uVar8 != 0) {
      uVar2 = FUN_ram_000499c4(param_1,iVar3,(char)param_2[1],auStack_38);
      *param_3 = uVar2;
      gp = 0x20004000;
      return 0;
    }
  }
  else if (uVar8 == 0x17) {
    uVar8 = *(uint *)(iVar3 + 0x10);
    goto LAB_ram_00049ca6;
  }
  if (DAT_ram_20001d4d != *(char *)(iVar3 + 9)) {
    iVar4 = FUN_ram_000487a4(*(char *)(iVar3 + 9),param_1,0,(char)param_2[1],auStack_38);
    if (iVar4 != 0) goto LAB_ram_00049c10;
    iVar5 = FUN_ram_00048726(auStack_38,(char)param_2[1]);
    if (iVar5 != 0) {
      *param_3 = 0;
      goto LAB_ram_00049c10;
    }
  }
  iVar4 = 0;
LAB_ram_00049c10:
  if (*(char *)(iVar3 + 2) == '\x03') {
    if (auStack_38[0] < *(ushort *)(iVar3 + 0xc)) {
      *(ushort *)(iVar3 + 0xc) = auStack_38[0];
    }
    FUN_ram_00048b8c(param_1,*(undefined2 *)(iVar3 + 0xc));
    uVar8 = (uint)DAT_ram_20001bcc;
    if ((0x1b < uVar8) && (uVar6 = (uint)*(ushort *)(iVar3 + 0xc), 0x17 < uVar6)) {
      uVar7 = uVar6 + 4;
      if ((uVar8 <= uVar6 + 3) && (uVar7 = uVar8, 0xfb < uVar8)) {
        uVar7 = 0xfb;
      }
      thunk_FUN_ram_000656da(param_1,uVar7 & 0xffff,0x4290);
    }
  }
  FUN_ram_000495b2(iVar3);
  gp = 0x20004000;
  return iVar4;
}

