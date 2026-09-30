/* Address: 00058850; name: FUN_00058850; body bytes: 76 */

void FUN_00058850(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = FUN_0003758e();
  if (iVar1 != 0) {
    iVar2 = FUN_0004bbec();
    iVar3 = FUN_0004baf8(param_1);
    if (iVar3 < iVar2) {
      FUN_0004cb2e(iVar1,0);
      iVar2 = FUN_00046bd6();
      iVar1 = FUN_0004cb76(iVar1,0);
      FUN_0004e538(*(undefined4 *)(param_1 + 0x2c),(iVar1 + iVar2) * *(int *)(param_1 + 0x40),0);
      FUN_0004d3d8(*(undefined4 *)(param_1 + 0x2c));
      return;
    }
  }
  return;
}

