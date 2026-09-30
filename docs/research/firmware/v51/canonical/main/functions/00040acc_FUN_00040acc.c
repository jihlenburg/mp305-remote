/* Address: 00040acc; name: FUN_00040acc; body bytes: 60 */

void FUN_00040acc(int param_1,undefined2 param_2,undefined4 param_3)

{
  int iVar1;
  int local_30;
  int local_2c;
  undefined2 local_28;
  undefined4 local_20;
  
  FUN_0004a5da(&local_30,0x1c);
  local_30 = param_1;
  local_2c = param_1;
  local_28 = param_2;
  local_20 = param_3;
  iVar1 = FUN_000467fc(param_1 + 0x2e0,&local_30,1);
  if (iVar1 == 1) {
    FUN_000467fc(param_1 + 0x2e0,&local_30,0);
  }
  return;
}

