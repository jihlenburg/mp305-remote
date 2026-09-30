/* Address: 000461e8; name: FUN_000461e8; body bytes: 96 */

void FUN_000461e8(int param_1,undefined1 *param_2,int param_3)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  iVar5 = 0;
  if (*(int *)(param_1 + 0x38) == 0) {
    *param_2 = 0;
  }
  else {
    uVar2 = FUN_00050a64();
    uVar3 = 0;
    while ((uVar3 < uVar2 && (*(int *)(param_1 + 0x44) != iVar5))) {
      if (*(char *)(*(int *)(param_1 + 0x38) + uVar3) == '\n') {
        iVar5 = iVar5 + 1;
      }
      uVar3 = uVar3 + 1;
    }
    for (uVar4 = 0;
        ((uVar3 < uVar2 && (cVar1 = *(char *)(*(int *)(param_1 + 0x38) + uVar3), cVar1 != '\n')) &&
        ((param_3 == 0 || (uVar4 < param_3 - 1U)))); uVar4 = uVar4 + 1) {
      param_2[uVar4] = cVar1;
      uVar3 = uVar3 + 1;
    }
    param_2[uVar4] = 0;
  }
  return;
}

