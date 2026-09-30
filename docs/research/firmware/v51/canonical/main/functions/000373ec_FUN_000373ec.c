/* Address: 000373ec; name: FUN_000373ec; body bytes: 68 */

uint FUN_000373ec(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  iVar1 = FUN_0003758e();
  uVar4 = 0;
  if (iVar1 != 0) {
    iVar2 = *(int *)(iVar1 + 0x18);
    FUN_0004cb2e(iVar1,0);
    iVar3 = FUN_00046bd6();
    iVar1 = FUN_0004cb76(iVar1,0);
    uVar4 = ((param_2 - iVar2) + iVar1 / 2) / (iVar1 + iVar3);
    if (*(uint *)(param_1 + 0x3c) <= uVar4) {
      uVar4 = *(uint *)(param_1 + 0x3c) - 1;
    }
  }
  return uVar4;
}

