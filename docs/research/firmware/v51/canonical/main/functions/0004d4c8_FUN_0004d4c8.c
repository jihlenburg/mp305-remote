/* Address: 0004d4c8; name: FUN_0004d4c8; body bytes: 56 */

void FUN_0004d4c8(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  local_20 = param_1;
  local_1c = param_2;
  local_18 = param_3;
  local_14 = param_4;
  iVar1 = FUN_0004bbb0();
  FUN_0003d9a4(&local_20,param_1 + 0x14);
  local_20 = local_20 - iVar1;
  local_1c = local_1c - iVar1;
  local_18 = local_18 + iVar1;
  local_14 = local_14 + iVar1;
  FUN_0004af50(param_1,&local_20);
  return;
}

