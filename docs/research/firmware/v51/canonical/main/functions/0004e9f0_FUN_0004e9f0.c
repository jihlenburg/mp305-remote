/* Address: 0004e9f0; name: FUN_0004e9f0; body bytes: 46 */

void FUN_0004e9f0(undefined4 param_1,undefined4 param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 unaff_r4;
  undefined4 unaff_r5;
  undefined4 unaff_r6;
  
  FUN_0004ea28();
  FUN_0004ea32(param_1,param_2,param_3);
  FUN_0004ea3c(param_1,param_2,param_3);
  FUN_000637cc(param_1,param_3 & 0xff0000,0x11,0,unaff_r4,unaff_r5,unaff_r6);
  uVar1 = FUN_00037610(param_1,param_3);
  if ((param_3 == 0) && (iVar2 = FUN_00050c04(0x11,0x20), iVar2 != 0)) {
    FUN_0004d3d8(param_1);
  }
  FUN_00050ef2(uVar1,0x11,param_2);
  FUN_0004dedc(param_1,param_3,0x11);
  return;
}

