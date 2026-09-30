/* Address: 0004a910; name: FUN_0004a910; body bytes: 328 */

void FUN_0004a910(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  if (*(int *)(param_1 + 0x34) != 0) {
    FUN_0004e6e2(*(int *)(param_1 + 0x34),*(undefined4 *)(param_1 + 0x2c));
  }
  if (param_2 == 0) {
    FUN_0004a6b8(param_1);
  }
  else {
    piVar2 = (int *)FUN_0004a162(param_1 + 0x5c);
    if (piVar2 == (int *)0x0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    *piVar2 = param_2;
    *(char *)(param_1 + 0x68) = *(char *)(param_1 + 0x68) + '\x01';
    FUN_0004e6e2(param_2,*(undefined4 *)(param_1 + 0x30));
  }
  *(int *)(param_1 + 0x34) = param_2;
  if (*(int *)(param_1 + 0x58) != 0) {
    if (*(int *)(param_1 + 0x48) == 0) {
      FUN_0004e0e6(*(int *)(param_1 + 0x58),1);
    }
    else {
      FUN_0004aaf6();
    }
  }
  if (*(int *)(param_1 + 0x48) == 0) {
    if ((*(byte *)(param_1 + 0x68) < 2) && (-1 < (int)((uint)*(byte *)(param_1 + 0x6a) << 0x1c)))
    goto LAB_0004a9c0;
LAB_0004a9ae:
    FUN_0004e00e(*(undefined4 *)(param_1 + 0x3c),1);
    FUN_0004aa6e(*(undefined4 *)(param_1 + 0x3c),2);
  }
  else {
    if ((*(byte *)(param_1 + 0x6a) & 1) != 0) {
      if ((int)((uint)*(byte *)(param_1 + 0x6a) << 0x1c) < 0) {
        FUN_0004e00e();
        FUN_0004aa6e(*(undefined4 *)(param_1 + 0x50),2);
      }
      else {
        FUN_0004aa6e(*(undefined4 *)(param_1 + 0x50),1);
        FUN_0004e00e(*(undefined4 *)(param_1 + 0x50),2);
      }
    }
    if (1 < *(byte *)(param_1 + 0x68)) goto LAB_0004a9ae;
LAB_0004a9c0:
    FUN_0004aa6e(*(undefined4 *)(param_1 + 0x3c),1);
    FUN_0004e00e(*(undefined4 *)(param_1 + 0x3c),2);
  }
  FUN_0004e5a6(param_1,0x20,0);
  iVar1 = *(int *)(param_1 + 0x38);
  if ((iVar1 == 0) || (*(int *)(param_1 + 0x34) == 0)) {
    return;
  }
  uVar3 = (*(byte *)(param_1 + 0x6a) & 7) >> 1;
  uVar4 = 0;
  if (uVar3 == 0) {
LAB_0004a8e4:
    FUN_0004d680(iVar1,uVar4);
    uVar5 = 1;
    uVar4 = *(undefined4 *)(param_1 + 0x34);
  }
  else {
    if (uVar3 != 1) {
      if (uVar3 != 2) goto LAB_0004a8b8;
      uVar4 = 1;
      goto LAB_0004a8e4;
    }
    FUN_0004d680(iVar1,0);
    uVar5 = 0;
    uVar4 = *(undefined4 *)(param_1 + 0x34);
  }
  FUN_0004e63c(uVar4,uVar5);
LAB_0004a8b8:
  FUN_0004dbe0(*(undefined4 *)(param_1 + 0x38));
  FUN_0004dbe0(*(undefined4 *)(param_1 + 0x34));
  FUN_0004ef90(*(undefined4 *)(param_1 + 0x38));
  iVar1 = FUN_0004baf8(*(undefined4 *)(param_1 + 0x38));
  if (iVar1 == 0) {
    FUN_0004aa6e(*(undefined4 *)(param_1 + 0x38),1);
    return;
  }
  FUN_0004e00e();
  return;
}

