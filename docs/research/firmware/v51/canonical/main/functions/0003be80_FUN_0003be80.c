/* Address: 0003be80; name: FUN_0003be80; body bytes: 184 */

undefined4
FUN_0003be80(int param_1,undefined4 param_2,int param_3,undefined4 *param_4,undefined4 *param_5)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  
  uVar1 = FUN_0004bbb0(param_2);
  FUN_0004bb3c(param_2,param_5);
  FUN_0003db32(param_5,uVar1);
  if (param_3 == 2) {
    local_50 = *param_5;
    uStack_4c = param_5[1];
    uStack_48 = param_5[2];
    local_44 = param_5[3];
    FUN_0004cc08(param_2,&local_50,0);
    iVar2 = FUN_0003db4c(&local_40,param_1 + 0x18,&local_50);
    if (iVar2 == 0) {
      return 0;
    }
    local_30 = local_40;
    uStack_2c = uStack_3c;
    uStack_28 = uStack_38;
    uStack_24 = uStack_34;
    FUN_0004cc08(param_2,&local_30,2);
    iVar2 = FUN_0003db4c(&local_30,&local_30,param_5);
    if (iVar2 == 0) {
      return 0;
    }
    *param_4 = local_30;
    param_4[1] = uStack_2c;
    param_4[2] = uStack_28;
    param_4[3] = uStack_24;
    FUN_0003db32(param_4,5);
  }
  else {
    if (param_3 != 1) {
      return 0;
    }
    iVar2 = FUN_0003db4c(&local_50,param_1 + 0x18,param_5);
    if (iVar2 == 0) {
      return 0;
    }
    *param_4 = local_50;
    param_4[1] = uStack_4c;
    param_4[2] = uStack_48;
    param_4[3] = local_44;
  }
  return 1;
}

