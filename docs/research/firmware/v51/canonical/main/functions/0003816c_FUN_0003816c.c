/* Address: 0003816c; name: FUN_0003816c; body bytes: 148 */

void FUN_0003816c(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  FUN_0003e84e(*(undefined4 *)(param_1 + 0x2c),0xc000);
  iVar1 = FUN_00037294(*(undefined2 *)(param_1 + 0x34),(int)*(char *)(param_1 + 0x36),1);
  if (*(int *)(param_1 + 0x38) != 0) {
    for (uVar3 = 0; uVar3 < *(uint *)(param_1 + 0x3c); uVar3 = uVar3 + 1) {
      iVar2 = *(int *)(param_1 + 0x38);
      if ((*(short *)(iVar2 + uVar3 * 4) == *(short *)(param_1 + 0x34)) &&
         (*(char *)(iVar2 + uVar3 * 4 + 2) == *(char *)(param_1 + 0x36))) {
        FUN_0003ede0(*(undefined4 *)(param_1 + 0x2c),
                     (int)*(char *)(iVar2 + uVar3 * 4 + 3) + iVar1 + 6,0x8000);
      }
    }
  }
  if ((*(short *)(param_1 + 0x34) == *(short *)(param_1 + 0x30)) &&
     (*(char *)(param_1 + 0x36) == *(char *)(param_1 + 0x32))) {
    FUN_0003ede0(*(undefined4 *)(param_1 + 0x2c),(int)*(char *)(param_1 + 0x33) + iVar1 + 6,0x4000);
    return;
  }
  return;
}

