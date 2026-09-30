/* Address: 0004eae2; name: FUN_0004eae2; body bytes: 44 */

void FUN_0004eae2(undefined4 param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int local_10;
  
  local_10 = param_4;
  iVar1 = FUN_0004bc4c(param_1,1,&local_10,0);
  if (iVar1 == 1) {
    if (local_10 == param_2) {
      return;
    }
  }
  else if (iVar1 != 0) {
    return;
  }
  FUN_0004eac4(param_1,param_2,0);
  return;
}

