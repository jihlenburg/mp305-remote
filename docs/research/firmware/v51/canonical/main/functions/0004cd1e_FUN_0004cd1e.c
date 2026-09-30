/* Address: 0004cd1e; name: FUN_0004cd1e; body bytes: 38 */

int FUN_0004cd1e(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = FUN_0004bc8c();
  iVar2 = *(int *)(param_1 + 0x14);
  if (iVar1 != 0) {
    iVar4 = *(int *)(iVar1 + 0x14);
    iVar3 = FUN_0004bf20(iVar1);
    iVar1 = FUN_0004c9e8(iVar1,0);
    iVar2 = ((iVar2 - iVar4) + iVar3) - iVar1;
  }
  return iVar2;
}

