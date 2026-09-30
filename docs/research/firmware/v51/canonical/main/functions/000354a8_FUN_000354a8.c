/* Address: 000354a8; name: FUN_000354a8; body bytes: 310 */

undefined4 FUN_000354a8(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar1 = FUN_0004b384();
  FUN_0004e84a(uVar1,0x84,0x38);
  FUN_0004ab24(uVar1,&DAT_1fffb940,0);
  FUN_0004e00e(uVar1,0x10);
  uVar2 = FUN_0004b384(uVar1);
  uVar3 = FUN_0004f078(100);
  FUN_0004e84a(uVar2,0,uVar3);
  FUN_0004ab24(uVar2,&DAT_1fffb940,0);
  uVar2 = FUN_00048d88(uVar1);
  FUN_0004eab0(uVar2,&DAT_000730fc,0);
  uVar3 = FUN_0004029c();
  FUN_0004ea90(uVar2,uVar3,0);
  FUN_0004ac0a(uVar2,7,0);
  FUN_000499de(uVar2,"%02d.%02d",DAT_1fffab78 / 100,(uint)DAT_1fffab78 % 100);
  uVar2 = FUN_0004b384(uVar1);
  FUN_0004e84a(uVar2,0x15,0x12);
  FUN_0004ab24(uVar2,&DAT_1fffb940,0);
  uVar3 = FUN_0004029c();
  FUN_0004e8b2(uVar2,uVar3,0);
  FUN_0004ac0a(uVar2,1,0x6e,4);
  uVar3 = FUN_00047698(uVar2);
  FUN_00047d8e(uVar3,&DAT_0007bb38);
  FUN_0004ac0a(uVar3,1,2,3);
  FUN_0004e980(uVar3,0xff,0);
  uVar4 = FUN_0004037c(0xffffff);
  FUN_0004e960(uVar3,uVar4,0);
  FUN_0004aa6e(uVar2,1);
  uVar3 = FUN_00048d88(uVar1);
  FUN_0004eab0(uVar3,&DAT_00071bf8,0);
  uVar4 = FUN_0004029c();
  FUN_0004ea90(uVar3,uVar4,0);
  FUN_00049974(uVar3,&DAT_00035600);
  FUN_0004ac28(uVar3,uVar2,0xe,0,5);
  return uVar1;
}

