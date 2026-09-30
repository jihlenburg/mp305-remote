/* Address: 0004e388; name: FUN_0004e388; body bytes: 198 */

void FUN_0004e388(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (param_2 == 0 && param_3 == 0) {
    return;
  }
  FUN_0004ef90(param_1);
  iVar1 = FUN_0004bf20(param_1);
  param_2 = param_2 - iVar1;
  iVar2 = FUN_0004c5be(param_1,0);
  if (iVar2 == 1) {
    if (param_2 < 0) goto LAB_0004e3de;
    if (param_2 < 1) goto LAB_0004e400;
    iVar2 = FUN_0004bd90(param_1);
    iVar3 = FUN_0004be44(param_1);
    iVar2 = iVar2 + iVar3;
    if (iVar2 < 0) {
      iVar2 = 0;
    }
    if (param_2 <= iVar2) goto LAB_0004e400;
  }
  else {
    if (0 < param_2) {
LAB_0004e3de:
      param_2 = 0;
      goto LAB_0004e400;
    }
    if (-1 < param_2) goto LAB_0004e400;
    iVar2 = FUN_0004bd90(param_1);
    iVar3 = FUN_0004be44(param_1);
    iVar2 = iVar2 + iVar3;
    if (iVar2 < 0) {
      iVar2 = 0;
    }
    iVar2 = -iVar2;
    if (iVar2 <= param_2) goto LAB_0004e400;
  }
  param_2 = iVar2;
LAB_0004e400:
  iVar2 = FUN_0004bf2c(param_1);
  param_3 = param_3 - iVar2;
  if (param_3 < 1) {
    if (param_3 < 0) {
      iVar4 = FUN_0004bf14(param_1);
      iVar3 = FUN_0004bca4(param_1);
      iVar4 = iVar4 + iVar3;
      if (iVar4 < 0) {
        iVar4 = 0;
      }
      if (param_3 < -iVar4) {
        param_3 = -iVar4;
      }
    }
  }
  else {
    param_3 = 0;
  }
  if (param_2 + iVar1 == 0 && param_3 + iVar2 == 0) {
    return;
  }
  FUN_0004e25c(param_1,param_2 + iVar1,param_3 + iVar2,param_4);
  return;
}

