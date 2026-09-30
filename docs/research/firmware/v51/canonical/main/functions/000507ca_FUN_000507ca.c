/* Address: 000507ca; name: FUN_000507ca; body bytes: 28 */

void FUN_000507ca(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  char cStack_38;
  char acStack_37 [19];
  char acStack_24 [16];
  
  *(undefined4 *)(param_1 + 0x78) = param_3;
  *(undefined4 *)(param_1 + 0x7c) = param_2;
  if (*(int *)(param_1 + 0x78) < *(int *)(param_1 + 0x74)) {
    *(int *)(param_1 + 0x74) = *(int *)(param_1 + 0x78);
  }
  if (*(int *)(param_1 + 0x74) < *(int *)(param_1 + 0x7c)) {
    *(int *)(param_1 + 0x74) = *(int *)(param_1 + 0x7c);
  }
  pcVar5 = &cStack_38;
  FUN_0001049c(&cStack_38,0x14);
  iVar6 = 0;
  if (*(int *)(param_1 + 0x7c) < 0) {
    if (*(int *)(param_1 + 0x74) < 0) {
      cStack_38 = '-';
    }
    else {
      cStack_38 = '+';
    }
    pcVar5 = acStack_37;
  }
  else {
    iVar6 = 1;
  }
  iVar4 = *(int *)(param_1 + 0x74);
  if (iVar4 < 1) {
    iVar4 = -iVar4;
  }
  FUN_00050540(acStack_24,0xe,&DAT_00050940,iVar4);
  iVar4 = FUN_00050a64(acStack_24);
  iVar3 = (*(byte *)(param_1 + 0x84) & 0xf) - iVar4;
  if (iVar3 != 0) {
    for (; -1 < iVar4; iVar4 = iVar4 + -1) {
      acStack_24[iVar4 + iVar3] = acStack_24[iVar4];
    }
    for (iVar4 = 0; iVar4 < iVar3; iVar4 = iVar4 + 1) {
      acStack_24[iVar4] = '0';
    }
  }
  uVar1 = *(uint *)(param_1 + 0x84);
  if ((uVar1 & 0xf0) == 0) {
    uVar1 = uVar1 & 0xf;
  }
  else {
    uVar1 = (uVar1 & 0xff) >> 4;
  }
  for (iVar4 = 0; (iVar4 < (int)uVar1 && (acStack_24[iVar4] != '\0')); iVar4 = iVar4 + 1) {
    *pcVar5 = acStack_24[iVar4];
    pcVar5 = pcVar5 + 1;
  }
  if ((*(byte *)(param_1 + 0x84) & 0xf0) != 0) {
    *pcVar5 = '.';
    while( true ) {
      pcVar5 = pcVar5 + 1;
      if ((int)(*(byte *)(param_1 + 0x84) & 0xf) <= iVar4) break;
      if (acStack_24[iVar4] == '\0') break;
      *pcVar5 = acStack_24[iVar4];
      iVar4 = iVar4 + 1;
    }
  }
  FUN_000524bc(param_1,&cStack_38);
  uVar2 = *(byte *)(param_1 + 0x84) & 0xf;
  for (iVar4 = *(int *)(param_1 + 0x80); 9 < iVar4; iVar4 = iVar4 / 10) {
    uVar2 = uVar2 - 1;
  }
  if (uVar1 < uVar2) {
    uVar2 = uVar2 + 1;
  }
  FUN_00052370(param_1,uVar2 - iVar6);
  return;
}

