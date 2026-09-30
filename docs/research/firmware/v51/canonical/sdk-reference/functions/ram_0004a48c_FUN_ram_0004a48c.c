/* Address: ram:0004a48c; name: FUN_ram_0004a48c; body bytes: 464 */

int FUN_ram_0004a48c(undefined4 param_1,uint *param_2,undefined1 *param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  code *pcVar5;
  char acStack_50 [2];
  undefined2 uStack_4e;
  undefined1 uStack_4c;
  undefined2 *apuStack_48 [9];
  
  gp = 0x20004000;
  bVar1 = *(byte *)((int)param_2 + 2);
  if (bVar1 == 0x1e) {
    iVar2 = FUN_ram_0004a3c6();
    if ((iVar2 != 0) && (1 < (byte)(*(char *)(iVar2 + 2) + 2U))) {
      FUN_ram_000487a4(*(undefined1 *)(iVar2 + 3),param_1,0,0x1e,0);
      FUN_ram_0004a3aa(iVar2);
    }
  }
  else {
    uVar4 = *param_2;
    iVar2 = 0;
    if ((((uVar4 & 0xffff00) == 0x120100) || (iVar2 = FUN_ram_0004a3c6(), iVar2 == 0)) ||
       (*(char *)(iVar2 + 4) == '\0')) {
      if (DAT_ram_200019c2 == -1) {
        gp = 0x20004000;
        return 6;
      }
      if (0x18 < bVar1) {
        gp = 0x20004000;
        return 6;
      }
      iVar3 = (bVar1 >> 1) - 1;
      if ((code *)(&PTR_LAB_ram_00043a10_ram_0006bfa8)[iVar3 * 2] == (code *)0x0) {
        gp = 0x20004000;
        return 6;
      }
      pcVar5 = (code *)(&PTR_LAB_ram_00049dbe_ram_0006bfac)[iVar3 * 2];
      if (pcVar5 == (code *)0x0) {
        gp = 0x20004000;
        return 6;
      }
      if (((uVar4 & 0xffff) != 0) && (bVar1 != 0x12)) {
        gp = 0x20004000;
        return 6;
      }
      iVar3 = (*(code *)(&PTR_LAB_ram_00043a10_ram_0006bfa8)[iVar3 * 2])
                        ((char)*param_2,*(undefined1 *)((int)param_2 + 1),param_2[2],
                         (short)param_2[1],apuStack_48);
      if (iVar3 != 0) {
        gp = 0x20004000;
        return iVar3;
      }
      iVar3 = (*pcVar5)(param_1,apuStack_48);
      if (iVar3 == 0) {
        if (*(char *)((int)param_2 + 2) != '\x04') {
          iVar3 = FUN_ram_000487a4(DAT_ram_200019c2,param_1,0,*(char *)((int)param_2 + 2),
                                   apuStack_48);
          if (iVar3 != 0) {
            gp = 0x20004000;
            return iVar3;
          }
          iVar3 = FUN_ram_00048726(apuStack_48,*(undefined1 *)((int)param_2 + 2));
          if (iVar3 != 0) {
            *param_3 = 0;
          }
          if (((*param_2 & 0xffff00) != 0x120100) && (iVar2 != 0)) {
            *(undefined1 *)(iVar2 + 4) = *(undefined1 *)((int)param_2 + 2);
            gp = 0x20004000;
            return 0;
          }
        }
      }
      else {
        if (*(char *)((int)param_2 + 1) != '\0') {
          gp = 0x20004000;
          return iVar3;
        }
        acStack_50[0] = *(char *)((int)param_2 + 2);
        uStack_4c = (undefined1)iVar3;
        if (acStack_50[0] == '\x0e') {
          apuStack_48[0]._0_2_ = *apuStack_48[0];
        }
        else {
        }
        uStack_4e = apuStack_48[0]._0_2_;
        iVar2 = FUN_ram_00043428(param_1,acStack_50);
        if (iVar2 != 0) {
          iVar2 = FUN_ram_00048a38(param_1,0x16,1,acStack_50);
          gp = 0x20004000;
          return iVar2;
        }
      }
    }
    else if (-1 < *(char *)(iVar2 + 4)) {
      FUN_ram_00048828(param_1);
      *(byte *)(iVar2 + 4) = *(byte *)(iVar2 + 4) | 0x80;
    }
  }
  return 0;
}

