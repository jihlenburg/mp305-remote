/* Address: 0004e8b2; name: FUN_0004e8b2; body bytes: 32 */

void FUN_0004e8b2(undefined4 param_1,undefined3 param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  FUN_000637cc(param_1,param_3 & 0xff0000,0x1c,0);
  uVar1 = FUN_00037610(param_1,param_3);
  if ((param_3 == 0) && (iVar2 = FUN_00050c04(0x1c,0x20), iVar2 != 0)) {
    FUN_0004d3d8(param_1);
  }
  FUN_00050ef2(uVar1,0x1c,param_2);
  FUN_0004dedc(param_1,param_3,0x1c);
  return;
}

