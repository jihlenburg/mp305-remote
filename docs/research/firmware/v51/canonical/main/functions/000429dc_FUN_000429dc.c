/* Address: 000429dc; name: FUN_000429dc; body bytes: 112 */

void FUN_000429dc(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  
  iVar1 = FUN_0004035a(*(undefined1 *)(param_1 + 0x14));
  if (iVar1 != 0) {
    iVar1 = FUN_00040c36(param_1,param_1 + 4);
    uVar2 = FUN_0004a318(0x30);
    *(undefined4 *)(iVar1 + 0x4c) = uVar2;
    FUN_0004a404(uVar2,param_2,0x30);
    *(undefined1 *)(iVar1 + 4) = 10;
    piVar4 = *(int **)(iVar1 + 0x4c);
    piVar4[4] = param_1;
    if ((*piVar4 != 0) && (iVar3 = FUN_0004cd84(*piVar4,0x80000), iVar3 != 0)) {
      FUN_0004e00e(*piVar4,0x80000);
      FUN_0004e5a6(*param_2,0x1f,iVar1);
      FUN_0004aa6e(*piVar4,0x80000);
    }
    FUN_0004197c(param_1,iVar1);
    return;
  }
  return;
}

