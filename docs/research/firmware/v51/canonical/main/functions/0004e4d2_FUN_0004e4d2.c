/* Address: 0004e4d2; name: FUN_0004e4d2; body bytes: 62 */

void FUN_0004e4d2(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_20 = param_3;
  local_1c = param_4;
  FUN_0004ef90();
  local_20 = 0;
  local_1c = 0;
  iVar1 = FUN_0004bc8c(param_1);
  iVar3 = param_1;
  while (iVar1 != 0) {
    FUN_0005e278(param_1 + 0x14,iVar3,&local_20,param_2);
    iVar2 = FUN_0004bc8c(iVar1);
    iVar3 = iVar1;
    iVar1 = iVar2;
  }
  return;
}

