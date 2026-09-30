/* Address: 0004eef4; name: FUN_0004eef4; body bytes: 8 */

void FUN_0004eef4(int param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  while( true ) {
    if (param_1 == 0) {
      return;
    }
    iVar1 = FUN_0004bc3e();
    iVar3 = -((int)(param_3 << 0x1e) >> 0x1f);
    if (iVar3 != 0) break;
    if (iVar1 == 2) {
      FUN_00063e88(param_1,param_2,1,0);
    }
    if ((param_3 & 1) == 0) {
      return;
    }
    param_1 = FUN_0004bc8c(param_1);
  }
  if ((param_3 & 1) != 0) {
    uVar2 = FUN_0004bc8c(param_1);
    FUN_0004eefc(uVar2,param_2,1,param_3);
  }
  if (iVar1 != 2) {
    return;
  }
  FUN_00063e88(param_1,param_2,1,iVar3);
  return;
}

