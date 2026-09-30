/* Address: 0004e994; name: FUN_0004e994; body bytes: 10 */

void FUN_0004e994(undefined4 param_1,undefined4 param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  FUN_000637cc(param_1,param_3 & 0xff0000,3,0);
  uVar1 = FUN_00037610(param_1,param_3);
  if ((param_3 == 0) && (iVar2 = FUN_00050c04(3,0x20), iVar2 != 0)) {
    FUN_0004d3d8(param_1);
  }
  FUN_00050ef2(uVar1,3,param_2);
  FUN_0004dedc(param_1,param_3,3);
  return;
}

