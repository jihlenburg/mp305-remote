/* Address: 0002948c; name: FUN_0002948c; body bytes: 228 */

void FUN_0002948c(undefined4 param_1,int *param_2,int *param_3,undefined4 param_4,undefined1 param_5
                 )

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  undefined1 *local_70 [5];
  undefined1 local_5c;
  undefined2 local_5b;
  undefined1 local_59;
  undefined4 uStack_30;
  int *piStack_2c;
  int *piStack_28;
  undefined4 local_24;
  
  uStack_30 = param_1;
  piStack_2c = param_2;
  piStack_28 = param_3;
  local_24 = param_4;
  FUN_0004a57a(local_70,0,0x2c);
  local_5b = (undefined2)local_24;
  local_59 = local_24._2_1_;
  local_5c = param_5;
  iVar1 = param_2[1];
  iVar4 = param_3[1];
  iVar2 = param_2[3];
  iVar5 = param_3[3];
  iVar3 = *param_2;
  iVar6 = *param_3;
  iVar7 = param_2[2];
  iVar8 = param_3[2];
  local_78 = param_2[2];
  local_7c = param_2[1];
  local_74 = param_3[1] + -1;
  local_80 = iVar3;
  local_70[0] = (undefined1 *)&local_80;
  if (iVar1 <= iVar4) {
    local_70[0] = (undefined1 *)&local_80;
    FUN_0004337c(param_1,local_70);
  }
  local_7c = param_3[3] + 1;
  local_74 = param_2[3];
  if (iVar2 >= iVar5) {
    FUN_0004337c(param_1,local_70);
  }
  local_80 = *param_2;
  local_78 = *param_3 + -1;
  if (iVar4 < iVar1) {
    local_7c = param_2[1];
  }
  else {
    local_7c = param_3[1];
  }
  if (iVar2 < iVar5) {
    local_74 = param_2[3];
  }
  else {
    local_74 = param_3[3];
  }
  if (iVar3 <= iVar6) {
    FUN_0004337c(param_1,local_70);
  }
  local_80 = param_3[2] + 1;
  local_78 = param_2[2];
  if (iVar8 <= iVar7) {
    FUN_0004337c(param_1,local_70);
  }
  return;
}

