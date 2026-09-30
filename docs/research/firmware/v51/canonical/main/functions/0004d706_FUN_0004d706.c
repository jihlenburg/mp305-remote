/* Address: 0004d706; name: FUN_0004d706; body bytes: 146 */

void FUN_0004d706(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = FUN_0004bf04();
  if (iVar1 == 0) {
    iVar1 = FUN_0004bf14(param_1);
    iVar2 = FUN_0004bca4(param_1);
    if ((iVar2 < 0) && (0 < iVar1)) {
      iVar3 = -iVar2;
      if (iVar1 < -iVar2) {
        iVar3 = iVar1;
      }
      FUN_0004e25c(param_1,0,iVar3,param_2);
    }
  }
  iVar1 = FUN_0004bef4(param_1);
  if (iVar1 == 0) {
    iVar1 = FUN_0004bd90(param_1);
    iVar2 = FUN_0004be44(param_1);
    iVar3 = FUN_0004c5be(param_1,0);
    if (iVar3 == 1) {
      if ((iVar1 < 0) && (0 < iVar2)) goto LAB_0004d78a;
    }
    else if ((iVar2 < 0) && (0 < iVar1)) {
      if (-iVar2 <= iVar1) {
        iVar1 = -iVar2;
      }
LAB_0004d78a:
      FUN_0004e25c(param_1,iVar1,0,param_2);
      return;
    }
  }
  return;
}

