/* Address: 0004cd44; name: FUN_0004cd44; body bytes: 38 */

int FUN_0004cd44(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = FUN_0004bc8c();
  iVar2 = *(int *)(param_1 + 0x18);
  if (iVar1 != 0) {
    iVar4 = *(int *)(iVar1 + 0x18);
    iVar3 = FUN_0004bf2c(iVar1);
    iVar1 = FUN_0004caa4(iVar1,0);
    iVar2 = ((iVar2 - iVar4) + iVar3) - iVar1;
  }
  return iVar2;
}

