/* Address: 0002b108; name: FUN_0002b108; body bytes: 504 */

undefined4 FUN_0002b108(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar1 = FUN_0003f5c0();
  FUN_0004e84a(uVar1,param_2,param_3);
  FUN_0004ab24(uVar1,&DAT_1fffb940,0);
  FUN_0004e8dc(uVar1,0);
  FUN_0003f9d4(uVar1,200);
  FUN_0003f98e(uVar1,0);
  FUN_0004e822(uVar1,0);
  FUN_0004ea6a(uVar1,0,0,0x20000);
  FUN_0004eac4(uVar1,1,0x60000);
  FUN_0003fa48(uVar1,0,0,0xbea);
  FUN_0003fa48(uVar1,1,0,0x13ec);
  uVar2 = FUN_0004b384(uVar1);
  FUN_0004e84a(uVar2,0x60,0x5c);
  FUN_0004ac0a(uVar2,0,2);
  FUN_0004ab24(uVar2,&DAT_1fffb940,0);
  uVar3 = FUN_0004037c(0x333333);
  FUN_0004e8b2(uVar2,uVar3,0);
  FUN_0004e8dc(uVar2,0x99,0);
  FUN_0004e00e(uVar2,0x10);
  FUN_0004aa6e(uVar2,1);
  uVar3 = FUN_00048d88(uVar2);
  FUN_0004e84a(uVar3,0x53,0x3fffffff);
  FUN_0004ac0a(uVar3,0,6,4);
  FUN_0004ab24(uVar3,&DAT_1fffb9d0,0);
  FUN_000499de(uVar3,"V-20.00V");
  uVar3 = FUN_00048d88(uVar2);
  FUN_0004e84a(uVar3,0x53,0x3fffffff);
  FUN_0004ac0a(uVar3,0,6,0x19);
  FUN_0004ab24(uVar3,&DAT_1fffb9dc,0);
  FUN_000499de(uVar3,"I-5.000A");
  uVar3 = FUN_00048d88(uVar2);
  FUN_0004e84a(uVar3,0x53,0x3fffffff);
  FUN_0004ac0a(uVar3,0,6,0x2e);
  FUN_0004ab24(uVar3,&DAT_1fffb9a0,0);
  FUN_000499de(uVar3,"P-100.0W");
  uVar3 = FUN_00048d88(uVar2);
  FUN_0004e84a(uVar3,0x5a,0x3fffffff);
  FUN_0004ac0a(uVar3,0,6,0x43);
  FUN_0004ab24(uVar3,&DAT_1fffb9a0,0);
  FUN_000499de(uVar3,"T-0:00:00");
  uVar3 = FUN_0003e808(uVar1);
  FUN_0004e84a(uVar3,0x1a);
  FUN_0004ac28(uVar3,uVar2,0x13,0,0);
  FUN_0004ab24(uVar3,&DAT_1fffb970,0);
  uVar2 = FUN_0004037c(0x999999);
  FUN_0004e8e6(uVar3,uVar2,0);
  uVar2 = FUN_00047698(uVar3);
  FUN_00047d8e(uVar2,&DAT_0007bab4);
  FUN_0004b128(uVar2);
  FUN_0004e980(uVar2,0xff,0);
  uVar4 = FUN_0004037c(0xffffff);
  FUN_0004e960(uVar2,uVar4,0);
  FUN_0004aa6e(uVar3,1);
  return uVar1;
}

