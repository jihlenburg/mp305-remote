/* Address: 0004eaba; name: FUN_0004eaba; body bytes: 10 */

void FUN_0004eaba(undefined4 param_1,undefined4 param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  FUN_000637cc(param_1,param_3 & 0xff0000,0x5b,0);
  uVar1 = FUN_00037610(param_1,param_3);
  if ((param_3 == 0) && (iVar2 = FUN_00050c04(0x5b,0x20), iVar2 != 0)) {
    FUN_0004d3d8(param_1);
  }
  FUN_00050ef2(uVar1,0x5b,param_2);
  FUN_0004dedc(param_1,param_3,0x5b);
  return;
}

