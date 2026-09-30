/* Address: 0005075c; name: FUN_0005075c; body bytes: 110 */

void FUN_0005075c(int param_1,uint param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  longlong lVar7;
  char cStack_38;
  char acStack_37 [19];
  char acStack_24 [12];
  
  if (10 < param_2) {
    param_2 = 10;
  }
  if (param_2 <= param_3) {
    param_3 = 0;
  }
  if (param_2 < 10) {
    lVar7 = FUN_0004f364(10,0,(int)(char)param_2);
    uVar3 = *(uint *)(param_1 + 0x78);
    uVar1 = (uint)(lVar7 + -1);
    iVar6 = (int)((ulonglong)(lVar7 + -1) >> 0x20);
    iVar4 = (int)uVar3 >> 0x1f;
    if ((int)((iVar6 - iVar4) - (uint)(uVar1 < uVar3)) < 0 !=
        (SBORROW4(iVar6,iVar4) != SBORROW4(iVar6 - iVar4,(uint)(uVar1 < uVar3)))) {
      *(uint *)(param_1 + 0x78) = uVar1;
    }
    uVar3 = *(uint *)(param_1 + 0x7c);
    iVar4 = (int)uVar3 >> 0x1f;
    uVar1 = 1 - (uint)lVar7;
    iVar6 = -(uint)(1 < (uint)lVar7) - (int)((ulonglong)lVar7 >> 0x20);
    if ((int)((iVar4 - iVar6) - (uint)(uVar3 < uVar1)) < 0 !=
        (SBORROW4(iVar4,iVar6) != SBORROW4(iVar4 - iVar6,(uint)(uVar3 < uVar1)))) {
      *(uint *)(param_1 + 0x7c) = uVar1;
    }
  }
  *(uint *)(param_1 + 0x84) =
       *(uint *)(param_1 + 0x84) & 0xffffff00 | param_2 & 0xf | (param_3 & 0xf) << 4;
  pcVar5 = &cStack_38;
  FUN_0001049c(&cStack_38,0x14);
  iVar4 = 0;
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
    iVar4 = 1;
  }
  iVar6 = *(int *)(param_1 + 0x74);
  if (iVar6 < 1) {
    iVar6 = -iVar6;
  }
  FUN_00050540(acStack_24,0xe,&DAT_00050940,iVar6);
  iVar6 = FUN_00050a64(acStack_24);
  iVar2 = (*(byte *)(param_1 + 0x84) & 0xf) - iVar6;
  if (iVar2 != 0) {
    for (; -1 < iVar6; iVar6 = iVar6 + -1) {
      acStack_24[iVar6 + iVar2] = acStack_24[iVar6];
    }
    for (iVar6 = 0; iVar6 < iVar2; iVar6 = iVar6 + 1) {
      acStack_24[iVar6] = '0';
    }
  }
  uVar1 = *(uint *)(param_1 + 0x84);
  if ((uVar1 & 0xf0) == 0) {
    uVar1 = uVar1 & 0xf;
  }
  else {
    uVar1 = (uVar1 & 0xff) >> 4;
  }
  for (iVar6 = 0; (iVar6 < (int)uVar1 && (acStack_24[iVar6] != '\0')); iVar6 = iVar6 + 1) {
    *pcVar5 = acStack_24[iVar6];
    pcVar5 = pcVar5 + 1;
  }
  if ((*(byte *)(param_1 + 0x84) & 0xf0) != 0) {
    *pcVar5 = '.';
    while( true ) {
      pcVar5 = pcVar5 + 1;
      if ((int)(*(byte *)(param_1 + 0x84) & 0xf) <= iVar6) break;
      if (acStack_24[iVar6] == '\0') break;
      *pcVar5 = acStack_24[iVar6];
      iVar6 = iVar6 + 1;
    }
  }
  FUN_000524bc(param_1,&cStack_38);
  uVar3 = *(byte *)(param_1 + 0x84) & 0xf;
  for (iVar6 = *(int *)(param_1 + 0x80); 9 < iVar6; iVar6 = iVar6 / 10) {
    uVar3 = uVar3 - 1;
  }
  if (uVar1 < uVar3) {
    uVar3 = uVar3 + 1;
  }
  FUN_00052370(param_1,uVar3 - iVar4);
  return;
}

