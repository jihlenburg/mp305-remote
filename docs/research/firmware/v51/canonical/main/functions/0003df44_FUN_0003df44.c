/* Address: 0003df44; name: FUN_0003df44; body bytes: 80 */

undefined4 FUN_0003df44(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  
  iVar1 = FUN_00052940(0);
  uVar4 = 0;
  while (iVar2 = iVar1, iVar2 != 0) {
    iVar1 = FUN_00052940(iVar2);
    if (((*(int *)(iVar2 + 8) == 0x3df99) && (piVar3 = *(int **)(iVar2 + 0xc), *piVar3 == param_1))
       && (piVar3[1] == param_2)) {
      FUN_000528ac(iVar2);
      FUN_00046bec(piVar3);
      uVar4 = 1;
    }
  }
  return uVar4;
}

