/* Address: ram:0004a778; name: FUN_ram_0004a778; body bytes: 256 */

int FUN_ram_0004a778(int param_1,short *param_2)

{
  int iVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  short *psVar6;
  
  gp = 0x20004000;
  uVar2 = *(undefined2 *)(param_1 + 2);
  iVar3 = FUN_ram_0004a124(uVar2);
  if (iVar3 != 0) {
    iVar1 = 0;
    if (*(char *)(param_1 + 8) == '\x01') {
      iVar4 = FUN_ram_0004a18a(param_1 + 8,iVar3);
      if (iVar4 == 0) {
        psVar6 = (short *)(iVar3 + 4);
        iVar4 = 0;
        do {
          if (*psVar6 == 0) break;
          uVar5 = 0x18;
          if ((iVar4 != 0xe) && (psVar6[6] != 0)) {
            uVar5 = 0x16;
          }
          iVar1 = FUN_ram_0004a6d0(*(undefined2 *)(param_1 + 2),*psVar6,*(undefined4 *)(psVar6 + 4),
                                   psVar6[2],psVar6[1],uVar5);
          if (iVar1 == 0x16) {
            psVar6[4] = 0;
            psVar6[5] = 0;
          }
          else if (iVar1 != 0) {
            *param_2 = *psVar6;
          }
          iVar4 = iVar4 + 1;
          psVar6 = psVar6 + 6;
        } while (iVar4 != 0xf);
      }
      else {
        iVar1 = FUN_ram_0004a6d0(*(undefined2 *)(param_1 + 2),*(undefined2 *)(iVar3 + 4),
                                 *(undefined4 *)(iVar3 + 0xc),*(undefined2 *)(iVar3 + 8),
                                 *(undefined2 *)(iVar3 + 6),0x18);
        if (iVar1 == 0x16) {
          *(undefined4 *)(iVar3 + 0xc) = 0;
        }
        else if (iVar1 != 0) {
          *param_2 = *(short *)(iVar3 + 4);
        }
      }
    }
    FUN_ram_0004a0d4(iVar3);
    if (iVar1 != 0) {
      if (iVar1 == 0x16) {
        gp = 0x20004000;
        return 0;
      }
      gp = 0x20004000;
      return iVar1;
    }
    uVar2 = *(undefined2 *)(param_1 + 2);
  }
  iVar3 = FUN_ram_00043e28(uVar2);
  if (iVar3 == 0) {
    return 0;
  }
  gp = 0x20004000;
  return 0x16;
}

