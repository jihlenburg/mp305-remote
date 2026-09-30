/* Address: 00046304; name: FUN_00046304; body bytes: 494 */

void FUN_00046304(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  
  FUN_0004aaf6(param_1,1,param_3,param_4,param_4);
  uVar2 = FUN_0004bc94(param_1);
  FUN_0004e6e2(*(undefined4 *)(param_1 + 0x2c),uVar2);
  FUN_0004d680(*(undefined4 *)(param_1 + 0x2c),0xffffffff);
  FUN_0004e00e(*(undefined4 *)(param_1 + 0x2c),1);
  FUN_0004e5a6(param_1,0x23,0);
  uVar2 = FUN_0003758e(param_1);
  FUN_00049a3a(uVar2,*(undefined4 *)(param_1 + 0x38));
  FUN_0004eae2(*(undefined4 *)(param_1 + 0x2c),0x3fffffff);
  FUN_0004ef90(uVar2);
  iVar3 = FUN_0004ccf8(*(undefined4 *)(param_1 + 0x2c));
  iVar4 = FUN_0004ccf8(param_1);
  if ((iVar3 <= iVar4) && ((bVar1 = *(byte *)(param_1 + 0x4c) & 0xf, bVar1 == 4 || (bVar1 == 8)))) {
    uVar5 = FUN_0004ccf8(param_1);
    FUN_0004eae2(*(undefined4 *)(param_1 + 0x2c),uVar5);
  }
  iVar3 = FUN_0004bbec(uVar2);
  iVar4 = FUN_0004c69c(*(undefined4 *)(param_1 + 0x2c),0);
  iVar6 = FUN_0004c924(*(undefined4 *)(param_1 + 0x2c),0,0x10);
  iVar7 = FUN_0004c924(*(undefined4 *)(param_1 + 0x2c),0,0x11);
  iVar4 = iVar3 + iVar6 + iVar4 + iVar7 + iVar4;
  bVar1 = *(byte *)(param_1 + 0x4c) & 0xf;
  iVar3 = iVar4;
  if (bVar1 == 8) {
    FUN_00040890();
    iVar6 = FUN_00040960();
    if (iVar6 < *(int *)(param_1 + 0x20) + iVar4) {
      FUN_00040890();
      iVar3 = FUN_00040960();
      iVar6 = *(int *)(param_1 + 0x18);
      if (iVar3 - *(int *)(param_1 + 0x20) < iVar6) {
        bVar1 = 4;
      }
      else {
        FUN_00040890();
        iVar6 = FUN_00040960();
        iVar6 = iVar6 - *(int *)(param_1 + 0x20);
      }
      iVar3 = iVar6 + -1;
    }
  }
  else if ((bVar1 == 4) && (*(int *)(param_1 + 0x18) - iVar4 < 0)) {
    FUN_00040890();
    iVar6 = FUN_00040960();
    iVar3 = *(int *)(param_1 + 0x18);
    if (*(int *)(param_1 + 0x18) < iVar6 - *(int *)(param_1 + 0x20)) {
      bVar1 = 8;
      FUN_00040890();
      iVar3 = FUN_00040960();
      iVar3 = iVar3 - *(int *)(param_1 + 0x20);
    }
  }
  if (iVar4 < iVar3) {
    iVar3 = iVar4;
  }
  FUN_0004e654(*(undefined4 *)(param_1 + 0x2c),iVar3);
  FUN_00058850(param_1);
  if (bVar1 == 8) {
    uVar8 = 0xd;
    uVar5 = *(undefined4 *)(param_1 + 0x2c);
  }
  else if (bVar1 == 4) {
    uVar8 = 10;
    uVar5 = *(undefined4 *)(param_1 + 0x2c);
  }
  else if (bVar1 == 1) {
    uVar8 = 0x10;
    uVar5 = *(undefined4 *)(param_1 + 0x2c);
  }
  else {
    if (bVar1 != 2) goto LAB_0004647a;
    uVar5 = *(undefined4 *)(param_1 + 0x2c);
    uVar8 = 0x13;
  }
  FUN_0004ac28(uVar5,param_1,uVar8,0,0);
LAB_0004647a:
  FUN_0004ef90(*(undefined4 *)(param_1 + 0x2c));
  bVar1 = *(byte *)(param_1 + 0x4c) & 0xf;
  if ((bVar1 == 1) || (bVar1 == 2)) {
    iVar3 = FUN_0004cd44(*(undefined4 *)(param_1 + 0x2c));
    iVar4 = FUN_0004cd6a(*(undefined4 *)(param_1 + 0x2c));
    FUN_00040890();
    iVar6 = FUN_00040960();
    if (iVar6 <= iVar4) {
      FUN_00040890();
      iVar6 = FUN_00040960();
      FUN_0004eb3a(*(undefined4 *)(param_1 + 0x2c),(iVar3 - (iVar4 - iVar6)) + -1);
    }
  }
  iVar3 = FUN_0004b108(uVar2,0,*(undefined4 *)(param_1 + 0x38));
  if (iVar3 == 2) {
    uVar5 = 2;
  }
  else if (iVar3 == 3) {
    uVar5 = 3;
  }
  else {
    uVar5 = 1;
  }
  FUN_0004ac0a(uVar2,uVar5,0);
  return;
}

