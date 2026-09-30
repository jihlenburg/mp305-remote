/* Address: 00050714; name: FUN_00050714; body bytes: 72 */

void FUN_00050714(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  char cStack_38;
  char acStack_37 [19];
  char acStack_24 [20];
  
  iVar1 = *(int *)(param_1 + 0x78);
  iVar5 = *(int *)(param_1 + 0x7c);
  iVar2 = iVar5;
  if (iVar5 < 1) {
    iVar2 = -iVar5;
  }
  if ((iVar1 <= iVar2) && (iVar1 = iVar5, iVar5 < 1)) {
    iVar1 = -iVar5;
  }
  iVar2 = FUN_0004f364(10,0,(int)(char)param_2);
  if (param_2 == 0) {
    *(undefined4 *)(param_1 + 0x80) = 1;
  }
  else if (iVar2 <= iVar1) {
    *(int *)(param_1 + 0x80) = iVar2;
  }
  pcVar6 = &cStack_38;
  FUN_0001049c(&cStack_38,0x14);
  iVar1 = 0;
  if (*(int *)(param_1 + 0x7c) < 0) {
    if (*(int *)(param_1 + 0x74) < 0) {
      cStack_38 = '-';
    }
    else {
      cStack_38 = '+';
    }
    pcVar6 = acStack_37;
  }
  else {
    iVar1 = 1;
  }
  iVar2 = *(int *)(param_1 + 0x74);
  if (iVar2 < 1) {
    iVar2 = -iVar2;
  }
  FUN_00050540(acStack_24,0xe,&DAT_00050940,iVar2);
  iVar2 = FUN_00050a64(acStack_24);
  iVar5 = (*(byte *)(param_1 + 0x84) & 0xf) - iVar2;
  if (iVar5 != 0) {
    for (; -1 < iVar2; iVar2 = iVar2 + -1) {
      acStack_24[iVar2 + iVar5] = acStack_24[iVar2];
    }
    for (iVar2 = 0; iVar2 < iVar5; iVar2 = iVar2 + 1) {
      acStack_24[iVar2] = '0';
    }
  }
  uVar3 = *(uint *)(param_1 + 0x84);
  if ((uVar3 & 0xf0) == 0) {
    uVar3 = uVar3 & 0xf;
  }
  else {
    uVar3 = (uVar3 & 0xff) >> 4;
  }
  for (iVar2 = 0; (iVar2 < (int)uVar3 && (acStack_24[iVar2] != '\0')); iVar2 = iVar2 + 1) {
    *pcVar6 = acStack_24[iVar2];
    pcVar6 = pcVar6 + 1;
  }
  if ((*(byte *)(param_1 + 0x84) & 0xf0) != 0) {
    *pcVar6 = '.';
    for (; (pcVar6 = pcVar6 + 1, iVar2 < (int)(*(byte *)(param_1 + 0x84) & 0xf) &&
           (acStack_24[iVar2] != '\0')); iVar2 = iVar2 + 1) {
      *pcVar6 = acStack_24[iVar2];
    }
  }
  FUN_000524bc(param_1,&cStack_38);
  uVar4 = *(byte *)(param_1 + 0x84) & 0xf;
  for (iVar2 = *(int *)(param_1 + 0x80); 9 < iVar2; iVar2 = iVar2 / 10) {
    uVar4 = uVar4 - 1;
  }
  if (uVar3 < uVar4) {
    uVar4 = uVar4 + 1;
  }
  FUN_00052370(param_1,uVar4 - iVar1);
  return;
}

