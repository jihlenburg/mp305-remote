/* Address: 0003a78c; name: FUN_0003a78c; body bytes: 354 */

void FUN_0003a78c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x70);
  iVar1 = FUN_0004cd84(iVar3,0x80,param_3,param_4,param_4);
  if (iVar1 == 0) {
    FUN_0003ddf0(param_1 + 0x7c,0xe0000001,0xe0000001,0x1fffffff,0x1fffffff);
  }
  else {
    iVar1 = FUN_0004bf04(iVar3);
    if (iVar1 == 1) {
      uVar2 = FUN_0003642c(iVar3,*(int *)(iVar3 + 0x18) + 1,0x1fffffff,0);
      *(undefined4 *)(param_1 + 0x80) = uVar2;
      iVar1 = *(int *)(iVar3 + 0x18) + -1;
LAB_0003a81c:
      uVar2 = FUN_0003642c(iVar3,0xe0000001,iVar1,0);
      *(undefined4 *)(param_1 + 0x88) = uVar2;
    }
    else {
      if (iVar1 == 2) {
        uVar2 = FUN_0003642c(iVar3,*(undefined4 *)(iVar3 + 0x20),0x1fffffff,0);
        *(undefined4 *)(param_1 + 0x80) = uVar2;
        iVar1 = *(int *)(iVar3 + 0x20);
        goto LAB_0003a81c;
      }
      if (iVar1 == 3) {
        iVar1 = FUN_0003db0a(iVar3 + 0x14);
        iVar1 = *(int *)(iVar3 + 0x18) + iVar1 / 2;
        uVar2 = FUN_0003642c(iVar3,iVar1 + 1,0x1fffffff,0);
        iVar1 = iVar1 + -1;
        *(undefined4 *)(param_1 + 0x80) = uVar2;
        goto LAB_0003a81c;
      }
      *(undefined4 *)(param_1 + 0x80) = 0xe0000001;
      *(undefined4 *)(param_1 + 0x88) = 0x1fffffff;
    }
    iVar1 = FUN_0004bef4(iVar3);
    if (iVar1 == 1) {
      uVar2 = FUN_00036328(iVar3,*(undefined4 *)(iVar3 + 0x14),0x1fffffff,0);
      *(undefined4 *)(param_1 + 0x7c) = uVar2;
      iVar1 = *(int *)(iVar3 + 0x14);
    }
    else if (iVar1 == 2) {
      uVar2 = FUN_00036328(iVar3,*(undefined4 *)(iVar3 + 0x1c),0x1fffffff,0);
      *(undefined4 *)(param_1 + 0x7c) = uVar2;
      iVar1 = *(int *)(iVar3 + 0x1c);
    }
    else {
      if (iVar1 != 3) {
        *(undefined4 *)(param_1 + 0x7c) = 0xe0000001;
        *(undefined4 *)(param_1 + 0x84) = 0x1fffffff;
        goto LAB_0003a8b8;
      }
      iVar1 = FUN_0003db28(iVar3 + 0x14);
      iVar1 = *(int *)(iVar3 + 0x14) + iVar1 / 2;
      uVar2 = FUN_00036328(iVar3,iVar1 + 1,0x1fffffff,0);
      iVar1 = iVar1 + -1;
      *(undefined4 *)(param_1 + 0x7c) = uVar2;
    }
    uVar2 = FUN_00036328(iVar3,0xe0000001,iVar1,0);
    *(undefined4 *)(param_1 + 0x84) = uVar2;
  }
  if (*(int *)(param_1 + 0x7c) == 0x1fffffff) {
    *(undefined4 *)(param_1 + 0x7c) = 0xe0000001;
  }
LAB_0003a8b8:
  if (*(int *)(param_1 + 0x80) == 0x1fffffff) {
    *(undefined4 *)(param_1 + 0x80) = 0xe0000001;
  }
  if (*(int *)(param_1 + 0x7c) == 0) {
    *(undefined4 *)(param_1 + 0x7c) = 0xe0000001;
  }
  if (*(int *)(param_1 + 0x84) == 0) {
    *(undefined4 *)(param_1 + 0x84) = 0x1fffffff;
  }
  if (*(int *)(param_1 + 0x80) == 0) {
    *(undefined4 *)(param_1 + 0x80) = 0xe0000001;
  }
  if (*(int *)(param_1 + 0x88) == 0) {
    *(undefined4 *)(param_1 + 0x88) = 0x1fffffff;
  }
  return;
}

