/* Address: 0004ba66; name: FUN_0004ba66; body bytes: 40 */

int FUN_0004ba66(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  
  piVar3 = *(int **)(param_1 + 8);
  iVar1 = 0;
  if (piVar3 != (int *)0x0) {
    for (uVar2 = 0; uVar2 < *(ushort *)(piVar3 + 10); uVar2 = uVar2 + 1) {
      if (**(int **)(*piVar3 + uVar2 * 4) == param_2) {
        iVar1 = iVar1 + 1;
      }
    }
  }
  return iVar1;
}

