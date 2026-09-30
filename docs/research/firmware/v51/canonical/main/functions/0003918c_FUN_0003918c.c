/* Address: 0003918c; name: FUN_0003918c; body bytes: 186 */

void FUN_0003918c(undefined4 param_1,int param_2,int param_3,int *param_4,int *param_5,
                 undefined4 *param_6,code *param_7)

{
  int iVar1;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined2 local_60;
  undefined1 local_5e;
  undefined4 local_5c;
  undefined4 local_58;
  int local_54;
  int iStack_50;
  int iStack_4c;
  int iStack_48;
  int local_44 [4];
  undefined1 auStack_34 [16];
  
  local_60 = *(undefined2 *)(param_2 + 0x48);
  local_5e = *(undefined1 *)(param_2 + 0x4a);
  local_5c = *(undefined4 *)(param_3 + 0x30);
  local_58 = *(undefined4 *)(param_3 + 0x34);
  if ((*(int *)(param_3 + 0x2c) == 0) || ((param_4 != (int *)0x0 && (*param_4 != -0x1fffffff)))) {
    local_70 = *param_6;
    uStack_6c = param_6[1];
    uStack_68 = param_6[2];
    uStack_64 = param_6[3];
    FUN_0003ddd6(&local_70,-*param_5,-param_5[1]);
    if (param_4 == (int *)0x0) {
      param_4 = local_44;
    }
    *param_4 = -0x1fffffff;
    param_4[1] = -0x1fffffff;
    param_4[2] = -0x1fffffff;
    param_4[3] = -0x1fffffff;
    while( true ) {
      iVar1 = FUN_00047740(param_3,&local_70,param_4);
      local_54 = *param_4;
      iStack_50 = param_4[1];
      iStack_4c = param_4[2];
      iStack_48 = param_4[3];
      FUN_0003ddd6(&local_54,*param_5,param_5[1]);
      if (iVar1 != 1) break;
      iVar1 = FUN_0003db4c(auStack_34,param_6,&local_54);
      if (iVar1 != 0) {
        (*param_7)(param_1,param_2,param_3,&local_60,&local_54,auStack_34);
      }
    }
  }
  else {
    (*param_7)(param_1,param_2,param_3,&local_60,param_5,param_6);
  }
  return;
}

