/* Address: 0004d528; name: FUN_0004d528; body bytes: 100 */

void FUN_0004d528(int param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  uVar1 = FUN_0004ba5c();
  for (uVar4 = 0; uVar4 < uVar1; uVar4 = uVar4 + 1) {
    iVar3 = *(int *)(**(int **)(param_1 + 8) + uVar4 * 4);
    if ((param_4 == 0) || (iVar2 = FUN_0004cd84(iVar3,0x40000), iVar2 == 0)) {
      *(int *)(iVar3 + 0x14) = *(int *)(iVar3 + 0x14) + param_2;
      *(int *)(iVar3 + 0x18) = *(int *)(iVar3 + 0x18) + param_3;
      *(int *)(iVar3 + 0x1c) = *(int *)(iVar3 + 0x1c) + param_2;
      *(int *)(iVar3 + 0x20) = *(int *)(iVar3 + 0x20) + param_3;
      FUN_0004d528(iVar3,param_2,param_3,0);
    }
  }
  return;
}

