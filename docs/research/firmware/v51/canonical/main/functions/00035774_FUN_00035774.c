/* Address: 00035774; name: FUN_00035774; body bytes: 84 */

undefined4 FUN_00035774(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = FUN_00047698();
  FUN_00047d8e(uVar1,&DAT_0007d60c);
  FUN_0004e980(uVar1,0xff,0);
  uVar2 = FUN_0004037c(0xffffff);
  FUN_0004e960(uVar1,uVar2,0);
  uVar2 = FUN_00048d88(uVar1);
  FUN_0004ab24(uVar2,&DAT_1fffb9b8,0);
  FUN_00049974(uVar2,param_2);
  FUN_0004ac0a(uVar2,7,6,0);
  return uVar1;
}

