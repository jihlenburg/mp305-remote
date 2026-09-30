/* Address: 0004a2ac; name: FUN_0004a2ac; body bytes: 104 */

void FUN_0004a2ac(int *param_1)

{
  int iVar1;
  int *piVar2;
  int extraout_r2;
  int iVar3;
  int extraout_r2_00;
  undefined8 uVar4;
  
  if (param_1 == (int *)0x0) {
    return;
  }
  uVar4 = FUN_0004a118();
  iVar1 = (int)((ulonglong)uVar4 >> 0x20);
  if ((int)uVar4 == iVar1) {
    iVar1 = FUN_0004a13c();
    param_1[1] = iVar1;
    if (iVar1 == 0) {
      param_1[2] = extraout_r2;
      return;
    }
    iVar3 = 0;
  }
  else {
    uVar4 = FUN_0004a14a(param_1,iVar1,0);
    iVar1 = (int)((ulonglong)uVar4 >> 0x20);
    piVar2 = (int *)(*param_1 + iVar1);
    if ((int)uVar4 == iVar1) {
      iVar1 = *piVar2;
      param_1[2] = iVar1;
      if (iVar1 == 0) {
        param_1[1] = extraout_r2_00;
        return;
      }
      FUN_00054110(param_1,iVar1,0);
      return;
    }
    iVar3 = *piVar2;
    iVar1 = FUN_0004a13c(param_1);
    FUN_00054110(param_1,iVar3,iVar1);
  }
  FUN_0005411c(param_1,iVar1,iVar3);
  return;
}

