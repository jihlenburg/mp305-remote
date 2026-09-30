/* Address: 00028700; name: FUN_00028700; body bytes: 402 */

undefined4 FUN_00028700(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  uVar1 = FUN_0004b384();
  FUN_0004e84a(uVar1,0x20,0xc);
  FUN_0004ab24(uVar1,&DAT_1fffb940,0);
  FUN_0004e8dc(uVar1,0);
  FUN_0004e00e(uVar1,0x10);
  uVar2 = FUN_00047698(uVar1);
  FUN_00047d8e(uVar2,&DAT_0007bffc);
  FUN_0004e980(uVar2,0xff,0);
  uVar3 = FUN_0004037c(0);
  FUN_0004e960(uVar2,uVar3,0);
  FUN_0004aa6e(uVar2,2);
  FUN_0004aa6e(uVar2,0x4000);
  if (DAT_1fffaada == '\0') {
    FUN_0004aa6e(uVar2,1);
  }
  else {
    FUN_0004e00e();
  }
  uVar3 = FUN_0004b384(uVar1);
  FUN_0004e84a(uVar3,0,7);
  FUN_0004ab24(uVar3,&DAT_1fffb940,0);
  uVar4 = FUN_0004037c(0);
  FUN_0004e8b2(uVar3,uVar4,0);
  FUN_0004aa6e(uVar3,2);
  FUN_0004aa6e(uVar3,0x4000);
  FUN_0004eae2(uVar3,((uint)DAT_1fffab06 * 0xf) / 100);
  uVar4 = FUN_0004b384(uVar1);
  FUN_0004e84a(uVar4,0x13,0xb);
  FUN_0004ab24(uVar4,&DAT_1fffb970,0);
  FUN_0004e91a(uVar4,1,0);
  FUN_0004ea60(uVar4,1,0);
  uVar5 = FUN_0004037c(0);
  uVar6 = FUN_0004b9de(uVar1,2);
  FUN_0004e8e6(uVar6,uVar5,0);
  FUN_0004aa6e(uVar4,2);
  FUN_0004aa6e(uVar4,0x4000);
  FUN_0004ac28(uVar4,uVar2,0x14,3,0);
  FUN_0004ac28(uVar3,uVar4,7,1,0);
  uVar2 = FUN_0004b384(uVar1);
  FUN_0004e84a(uVar2,2,7);
  FUN_0004ab24(uVar2,&DAT_1fffb940,0);
  uVar3 = FUN_0004037c(0);
  FUN_0004e8b2(uVar2,uVar3,0);
  FUN_0004aa6e(uVar2,2);
  FUN_0004aa6e(uVar2,0x4000);
  FUN_0004ac28(uVar2,uVar4,0x14,1,0);
  return uVar1;
}

