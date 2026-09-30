/* Address: 0002be54; name: FUN_0002be54; body bytes: 316 */

void FUN_0002be54(undefined4 param_1)

{
  undefined4 uVar1;
  
  DAT_1ffe0360 = FUN_0002bcf8();
  FUN_0004e7c2(DAT_1ffe0360,2,0x69);
  DAT_1ffe0364 = FUN_0004b384(param_1);
  FUN_0004e84a(DAT_1ffe0364,0x84,0x1e);
  FUN_0004e7c2(DAT_1ffe0364,2,0xa5);
  FUN_0004ab24(DAT_1ffe0364,&DAT_1fffb940,0);
  uVar1 = FUN_0004037c(0x333333);
  FUN_0004e8b2(DAT_1ffe0364,uVar1,0);
  FUN_0004aa6e(DAT_1ffe0364,2);
  FUN_0004e9f0(DAT_1ffe0364,0xfffffffe);
  uVar1 = FUN_00048d88(DAT_1ffe0364);
  FUN_0004ab24(uVar1,&DAT_1fffb9a0,0);
  FUN_00049974(uVar1,"I-SET");
  FUN_0004ac0a(uVar1,7,6,0);
  uVar1 = FUN_00048d88(DAT_1ffe0364);
  FUN_0004ab24(uVar1,&DAT_1fffb9a0,0);
  FUN_0004ac0a(uVar1,8,0xfffffffc);
  FUN_000499de(uVar1,"%01d.%03d A",DAT_1fffab76 / 1000,(uint)DAT_1fffab76 % 1000);
  uVar1 = FUN_00048d88(DAT_1ffe0364);
  FUN_0004ab24(uVar1,&DAT_1fffb9b8,0);
  FUN_00049974(uVar1,"SET : ");
  FUN_0004ac0a(uVar1,8,0xfffffffc,0);
  FUN_0004aa6e(uVar1,1);
  DAT_1ffe0368 = FUN_00035774(param_1,"SET : ");
  FUN_0004e7c2(DAT_1ffe0368,2,0xa5);
  FUN_0004aa6e(DAT_1ffe0368,1);
  DAT_1ffe036c = FUN_0004b384(param_1);
  FUN_0004e84a(DAT_1ffe036c,0x84,0x5a);
  FUN_0004e7c2(DAT_1ffe036c,2,0x69);
  FUN_0004ab24(DAT_1ffe036c,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe036c,0);
  FUN_0004aa6e(DAT_1ffe036c,2);
  return;
}

