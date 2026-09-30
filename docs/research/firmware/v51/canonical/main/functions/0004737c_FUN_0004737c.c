/* Address: 0004737c; name: FUN_0004737c; body bytes: 152 */

void FUN_0004737c(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  
  iVar1 = FUN_0004bbe2();
  if (iVar1 == 0) {
    return;
  }
  if (*(int **)(iVar1 + 0xc) != (int *)0x0) {
    if (**(int **)(iVar1 + 0xc) == param_1) {
      if ((*(byte *)(iVar1 + 0x1c) & 1) != 0) {
        *(byte *)(iVar1 + 0x1c) = *(byte *)(iVar1 + 0x1c) & 0xfe;
      }
      iVar2 = FUN_0004a118(iVar1);
      if ((iVar2 == *(int *)(iVar1 + 0xc)) &&
         (iVar2 = FUN_0004a14a(iVar1), iVar2 == *(int *)(iVar1 + 0xc))) {
        uVar3 = FUN_00037430(iVar1);
        FUN_0004e5a6(**(undefined4 **)(iVar1 + 0xc),0x11,uVar3);
      }
      else {
        FUN_00047304(iVar1);
      }
      if (*(int *)(iVar1 + 0xc) == 0) goto LAB_000473e2;
    }
    if (**(int **)(iVar1 + 0xc) == param_1) {
      *(undefined4 *)(iVar1 + 0xc) = 0;
    }
  }
LAB_000473e2:
  piVar4 = (int *)FUN_0004a118(iVar1);
  while( true ) {
    if (piVar4 == (int *)0x0) {
      return;
    }
    if (*piVar4 == param_1) break;
    piVar4 = (int *)FUN_0004a13c(iVar1,piVar4);
  }
  FUN_0004a2ac();
  FUN_00046bec(piVar4);
  if (*(int *)(param_1 + 8) == 0) {
    return;
  }
  *(undefined4 *)(*(int *)(param_1 + 8) + 4) = 0;
  return;
}

