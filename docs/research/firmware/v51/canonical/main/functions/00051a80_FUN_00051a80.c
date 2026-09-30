/* Address: 00051a80; name: FUN_00051a80; body bytes: 78 */

void FUN_00051a80(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  if ((param_1 != 0) && (param_3 != 0)) {
    iVar1 = FUN_00050a64();
    iVar2 = FUN_00050a64(param_3);
    if (iVar2 != 0) {
      iVar3 = FUN_00051c28(param_1,param_2);
      for (uVar4 = iVar1 + iVar2; (uint)(iVar3 + iVar2) <= uVar4; uVar4 = uVar4 - 1) {
        *(undefined1 *)(param_1 + uVar4) = *(undefined1 *)(param_1 + (uVar4 - iVar2));
      }
      FUN_0004a404(iVar3 + param_1,param_3,iVar2);
      return;
    }
  }
  return;
}

