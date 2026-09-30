/* Address: 000505e8; name: FUN_000505e8; body bytes: 364 */

void FUN_000505e8(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  bool bVar9;
  undefined8 uVar10;
  char cStack_38;
  char acStack_37 [19];
  char acStack_24 [20];
  
  iVar1 = FUN_0004b9b2(&DAT_0007ae84);
  if (iVar1 != 1) {
    return;
  }
  iVar1 = FUN_00046688(param_2);
  iVar2 = FUN_00046698(param_2);
  if (iVar1 != 8) {
    return;
  }
  FUN_00047eec();
  iVar1 = FUN_000482e0();
  if (iVar1 == 4) {
    FUN_0004bbe2(iVar2);
    iVar1 = FUN_000472d4();
    if (iVar1 != 0) {
      uVar6 = *(uint *)(iVar2 + 0x84) & 0xf;
      if (uVar6 < 2) {
        return;
      }
      if ((*(uint *)(iVar2 + 0x84) & 0x7ff) >> 9 == 2) {
        if (1 < *(int *)(iVar2 + 0x80)) goto LAB_0005067c;
        uVar3 = FUN_0004f364(10,0,uVar6 - 2);
        *(undefined4 *)(iVar2 + 0x80) = uVar3;
      }
      else {
        uVar10 = FUN_0004f364(10,0,uVar6 - 1);
        iVar1 = (int)((ulonglong)uVar10 >> 0x20);
        uVar6 = *(uint *)(iVar2 + 0x80);
        iVar7 = (int)uVar6 >> 0x1f;
        bVar9 = uVar6 < (uint)uVar10;
        if ((int)((iVar7 - iVar1) - (uint)bVar9) < 0 ==
            (SBORROW4(iVar7,iVar1) != SBORROW4(iVar7 - iVar1,(uint)bVar9))) {
          *(undefined4 *)(iVar2 + 0x80) = 10;
LAB_0005067c:
          iVar1 = *(int *)(iVar2 + 0x80) / 10;
          if (iVar1 < 1) {
            iVar1 = 1;
          }
          *(int *)(iVar2 + 0x80) = iVar1;
          goto LAB_00050848;
        }
      }
      iVar1 = *(int *)(iVar2 + 0x78);
      iVar5 = *(int *)(iVar2 + 0x7c);
      iVar7 = iVar5;
      if (iVar5 < 1) {
        iVar7 = -iVar5;
      }
      if ((iVar1 <= iVar7) && (iVar1 = iVar5, iVar5 < 1)) {
        iVar1 = -iVar5;
      }
      iVar7 = *(int *)(iVar2 + 0x80) * 10;
      if (iVar7 - iVar1 == 0 || iVar7 < iVar1) {
        *(int *)(iVar2 + 0x80) = iVar7;
      }
      goto LAB_00050848;
    }
  }
  iVar1 = FUN_00052350(iVar2);
  iVar7 = FUN_00050a64();
  iVar5 = *(int *)(iVar2 + 0x4c);
  if (*(char *)(iVar1 + iVar5) == '.') {
    FUN_000520c6(iVar2);
  }
  else {
    if (iVar5 == iVar7) {
      iVar7 = iVar7 + -1;
    }
    else {
      if ((iVar5 != 0) || (-1 < *(int *)(iVar2 + 0x7c))) goto LAB_000506b8;
      iVar7 = 1;
    }
    FUN_00052370(iVar2,iVar7);
  }
LAB_000506b8:
  uVar4 = *(uint *)(iVar2 + 0x84);
  uVar6 = *(uint *)(iVar2 + 0x4c);
  if (((uVar4 & 0xff) >> 4 < uVar6) && ((uVar4 & 0xf0) != 0)) {
    uVar6 = uVar6 - 1;
  }
  uVar6 = ((uVar4 & 0xf) - 1) - uVar6;
  if (*(int *)(iVar2 + 0x7c) < 0) {
    uVar6 = uVar6 + 1;
  }
  *(undefined4 *)(iVar2 + 0x80) = 1;
  for (uVar4 = 0; uVar4 < uVar6; uVar4 = uVar4 + 1) {
    *(int *)(iVar2 + 0x80) = *(int *)(iVar2 + 0x80) * 10;
  }
LAB_00050848:
  pcVar8 = &cStack_38;
  FUN_0001049c(&cStack_38,0x14);
  iVar1 = 0;
  if (*(int *)(iVar2 + 0x7c) < 0) {
    if (*(int *)(iVar2 + 0x74) < 0) {
      cStack_38 = '-';
    }
    else {
      cStack_38 = '+';
    }
    pcVar8 = acStack_37;
  }
  else {
    iVar1 = 1;
  }
  iVar7 = *(int *)(iVar2 + 0x74);
  if (iVar7 < 1) {
    iVar7 = -iVar7;
  }
  FUN_00050540(acStack_24,0xe,&DAT_00050940,iVar7);
  iVar7 = FUN_00050a64(acStack_24);
  iVar5 = (*(byte *)(iVar2 + 0x84) & 0xf) - iVar7;
  if (iVar5 != 0) {
    for (; -1 < iVar7; iVar7 = iVar7 + -1) {
      acStack_24[iVar7 + iVar5] = acStack_24[iVar7];
    }
    for (iVar7 = 0; iVar7 < iVar5; iVar7 = iVar7 + 1) {
      acStack_24[iVar7] = '0';
    }
  }
  uVar6 = *(uint *)(iVar2 + 0x84);
  if ((uVar6 & 0xf0) == 0) {
    uVar6 = uVar6 & 0xf;
  }
  else {
    uVar6 = (uVar6 & 0xff) >> 4;
  }
  for (iVar7 = 0; (iVar7 < (int)uVar6 && (acStack_24[iVar7] != '\0')); iVar7 = iVar7 + 1) {
    *pcVar8 = acStack_24[iVar7];
    pcVar8 = pcVar8 + 1;
  }
  if ((*(byte *)(iVar2 + 0x84) & 0xf0) != 0) {
    *pcVar8 = '.';
    for (; (pcVar8 = pcVar8 + 1, iVar7 < (int)(*(byte *)(iVar2 + 0x84) & 0xf) &&
           (acStack_24[iVar7] != '\0')); iVar7 = iVar7 + 1) {
      *pcVar8 = acStack_24[iVar7];
    }
  }
  FUN_000524bc(iVar2,&cStack_38);
  uVar4 = *(byte *)(iVar2 + 0x84) & 0xf;
  for (iVar7 = *(int *)(iVar2 + 0x80); 9 < iVar7; iVar7 = iVar7 / 10) {
    uVar4 = uVar4 - 1;
  }
  if (uVar6 < uVar4) {
    uVar4 = uVar4 + 1;
  }
  FUN_00052370(iVar2,uVar4 - iVar1);
  return;
}

