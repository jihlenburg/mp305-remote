/* Address: 0004de6c; name: FUN_0004de6c; body bytes: 64 */

void FUN_0004de6c(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int local_10;
  
  local_10 = param_4;
  iVar1 = FUN_0004bbb0();
  local_10 = 0;
  FUN_0004e5a6(param_1,0x18,&local_10);
  if (*(int *)(param_1 + 8) == 0) {
    if (local_10 != 0) {
      FUN_0004af28(param_1);
      *(int *)(*(int *)(param_1 + 8) + 0x24) = local_10;
    }
  }
  else {
    *(int *)(*(int *)(param_1 + 8) + 0x24) = local_10;
  }
  if (local_10 != iVar1) {
    FUN_0004d3d8(param_1);
  }
  return;
}

