/* Address: 0004bd50; name: FUN_0004bd50; body bytes: 54 */

void FUN_0004bd50(undefined4 param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = FUN_0003c9c4(param_1,0x5e59d);
  if (iVar1 == 0) {
    iVar1 = FUN_0004bf20(param_1);
  }
  else {
    iVar1 = -*(int *)(iVar1 + 0x2c);
  }
  *param_2 = iVar1;
  iVar1 = FUN_0003c9c4(param_1,0x5e5b3);
  if (iVar1 == 0) {
    iVar1 = FUN_0004bf2c(param_1);
  }
  else {
    iVar1 = -*(int *)(iVar1 + 0x2c);
  }
  param_2[1] = iVar1;
  return;
}

