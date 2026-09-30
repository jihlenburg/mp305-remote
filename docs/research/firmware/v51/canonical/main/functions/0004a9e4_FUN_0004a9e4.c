/* Address: 0004a9e4; name: FUN_0004a9e4; body bytes: 92 */

void FUN_0004a9e4(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0004675a();
  if ((*(int *)(iVar1 + 0x34) != 0) && (iVar2 = *(int *)(iVar1 + 0x40), iVar2 != 0)) {
    if (*(int *)(*(int *)(iVar1 + 0x34) + 0x2c) == 0) {
      FUN_0004aa6e(iVar2,1);
    }
    else {
      FUN_00049974(iVar2);
      FUN_0004e00e(*(undefined4 *)(iVar1 + 0x40),1);
    }
  }
  if ((*(int *)(iVar1 + 0x48) != 0) && (iVar2 = *(int *)(iVar1 + 0x54), iVar2 != 0)) {
    if (*(int *)(*(int *)(iVar1 + 0x48) + 0x2c) != 0) {
      FUN_00049974(iVar2);
      FUN_0004e00e(*(undefined4 *)(iVar1 + 0x54),1);
      return;
    }
    FUN_0004aa6e(iVar2,1);
    return;
  }
  return;
}

