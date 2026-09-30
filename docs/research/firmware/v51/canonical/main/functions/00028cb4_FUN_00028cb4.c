/* Address: 00028cb4; name: FUN_00028cb4; body bytes: 1046 */

void FUN_00028cb4(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined *puVar6;
  undefined4 uVar7;
  
  DAT_1ffe0700 = FUN_0004b384();
  uVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe0700,uVar2,uVar1);
  uVar1 = FUN_00037604();
  FUN_0004e7c2(DAT_1ffe0700,uVar1,0);
  FUN_0004ab24(DAT_1ffe0700,&DAT_1fffb940,0);
  uVar1 = FUN_0004029c();
  FUN_0004e8b2(DAT_1ffe0700,uVar1,0);
  FUN_0004e00e(DAT_1ffe0700,0x10);
  FUN_0004e822(DAT_1ffe0700,0);
  uVar1 = FUN_0004b384(DAT_1ffe0700);
  FUN_0004e84a(uVar1,200,0x1e);
  FUN_0004ac0a(uVar1,1,2);
  FUN_0004ab24(uVar1,&DAT_1fffb940,0);
  uVar1 = FUN_00048d88(uVar1);
  FUN_0004ab24(uVar1,&DAT_1fffb9c4,0);
  uVar2 = FUN_00015a5c(0x33);
  FUN_000499de(uVar1,&DAT_000290c4,uVar2);
  FUN_0004ea86(uVar1,2,0);
  FUN_0004b128(uVar1);
  uVar1 = FUN_0004b384(DAT_1ffe0700);
  iVar3 = FUN_00037604();
  FUN_0004e84a(uVar1,iVar3 + -4,2);
  FUN_0004ac0a(uVar1,2,0,0x1e);
  FUN_0004ab24(uVar1,&DAT_1fffb940,0);
  DAT_1ffe0704 = FUN_0003e808(DAT_1ffe0700);
  FUN_0004e84a(DAT_1ffe0704,100,0x1a);
  FUN_0004ac0a(DAT_1ffe0704,3,0xfffffffe);
  FUN_0004ab24(DAT_1ffe0704,&DAT_1fffb970,0);
  uVar1 = FUN_0004037c(0x999999);
  FUN_0004e8e6(DAT_1ffe0704,uVar1,0);
  uVar1 = FUN_00047698(DAT_1ffe0704);
  FUN_00047d8e(uVar1,&DAT_0007bab4);
  FUN_0004b128(uVar1);
  FUN_0004e980(uVar1,0xff,0);
  uVar2 = FUN_0004037c(0xffffff);
  FUN_0004e960(uVar1,uVar2,0);
  DAT_1ffe0708 = FUN_0003e808(DAT_1ffe0700);
  FUN_0004e84a(DAT_1ffe0708,0x46,0x1e);
  FUN_0004ac0a(DAT_1ffe0708,3,0xfffffffe,0x44);
  FUN_0004ab24(DAT_1ffe0708,&DAT_1fffb970,0);
  uVar1 = FUN_0004037c(0x333333);
  FUN_0004e8e6(DAT_1ffe0708,uVar1,0x80);
  uVar1 = FUN_00047698(DAT_1ffe0708);
  FUN_00047d8e(uVar1,&DAT_0007bab4);
  FUN_0004b128(uVar1);
  FUN_0004e980(uVar1,0xff,0);
  uVar2 = FUN_0004b384(DAT_1ffe0700);
  FUN_0004e84a(uVar2,0xaf,0x1e);
  FUN_0004ab24(uVar2,&DAT_1fffb940,0);
  uVar4 = FUN_0004037c(0x333333);
  FUN_0004e8b2(uVar2,uVar4,0);
  FUN_0004ac28(uVar2,DAT_1ffe0708,0x11,0xfffffffe,0);
  DAT_1ffe070c = FUN_00047698(uVar2);
  puVar6 = (undefined *)0x0;
  if (DAT_1fffaad0 != '\0') {
    if (DAT_1fffaad0 == '\x01') {
      puVar6 = &DAT_0007f128;
    }
    else {
      puVar6 = &DAT_0007f1c0;
    }
  }
  FUN_00047d8e(DAT_1ffe070c,puVar6);
  FUN_0004ac0a(DAT_1ffe070c,7,0xe,0);
  FUN_0004e980(DAT_1ffe070c,0xff,0);
  uVar4 = FUN_0004037c(0xffffff);
  FUN_0004e960(DAT_1ffe070c,uVar4,0);
  DAT_1ffe0710 = FUN_00048d88(uVar2);
  if (DAT_1fffaad0 == '\0') {
    puVar6 = &DAT_000290e4;
  }
  else {
    puVar6 = &DAT_1fffab24;
  }
  FUN_00049974(DAT_1ffe0710,puVar6);
  FUN_0004eae2(DAT_1ffe0710,0x7d);
  FUN_0004ac0a(DAT_1ffe0710,7,0x27,0);
  FUN_0004ab24(DAT_1ffe0710,&DAT_1fffb9a0,0);
  FUN_000498fc(DAT_1ffe0710,3);
  uVar4 = FUN_00048d88(DAT_1ffe0700);
  uVar5 = FUN_00015a5c(0x34);
  FUN_000499de(uVar4,&DAT_000290c4,uVar5);
  FUN_0004ab24(uVar4,&DAT_1fffb9ac,0);
  uVar7 = 0;
  FUN_0004ac28(uVar4,uVar2,0x11,0xfffffff6);
  DAT_1ffe0714 = FUN_0003e808(DAT_1ffe0700);
  FUN_0004e84a(DAT_1ffe0714,0x46,0x69);
  FUN_0004ac0a(DAT_1ffe0714,6,0xfffffffe);
  FUN_0004ab24(DAT_1ffe0714,&DAT_1fffb970,0);
  uVar2 = FUN_0004037c(0x333333);
  FUN_0004e8e6(DAT_1ffe0714,uVar2,0x80);
  uVar2 = FUN_0004b384(DAT_1ffe0714);
  FUN_0004e84a(uVar2,0x18);
  FUN_0004ab24(uVar2,&DAT_1fffb970,0);
  FUN_0004ac0a(uVar2,2,0,0xb);
  uVar4 = FUN_0004037c(0x333333);
  FUN_0004e8e6(uVar2,uVar4,0);
  uVar4 = FUN_0004b384(uVar2);
  FUN_0004e84a(uVar4,0x10,2);
  FUN_0004ab24(uVar4,&DAT_1fffb940,0);
  uVar5 = FUN_0004037c(0x333333);
  FUN_0004e8b2(uVar4,uVar5,0);
  FUN_0004b128(uVar4);
  uVar2 = FUN_0004b384(uVar2);
  FUN_0004e84a(uVar2,2,0x10);
  FUN_0004ab24(uVar2,&DAT_1fffb940,0);
  uVar4 = FUN_0004037c(0x333333);
  FUN_0004e8b2(uVar2,uVar4,0);
  FUN_0004b128(uVar2);
  uVar2 = FUN_00048d88(DAT_1ffe0714);
  uVar4 = FUN_00015a5c(0x35);
  FUN_000499de(uVar2,&DAT_000290c4,uVar4);
  FUN_0004ab24(uVar2,&DAT_1fffb9ac,0);
  FUN_0004ac0a(uVar2,5,0,0xfffffff6);
  FUN_0004ea86(uVar2,2,0);
  uVar4 = FUN_0004037c(0x333333);
  FUN_0004ea90(uVar2,uVar4,0);
  DAT_1ffe0718 = FUN_0004a0b8(DAT_1ffe0700);
  iVar3 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe0718,iVar3 + -0x4c,0x69);
  FUN_0004ac0a(DAT_1ffe0718,4,2,0xfffffffe);
  FUN_0004ab24(DAT_1ffe0718,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe0718,0);
  FUN_0004e822(DAT_1ffe0718,0);
  FUN_0004b288(DAT_1ffe0718);
  FUN_00021fe0(&DAT_000290e4,&DAT_0007f444);
  FUN_0004e0e6(DAT_1ffe0708,0x80);
  uVar2 = FUN_0004037c(0xffffff);
  FUN_0004e960(uVar1,uVar2,0);
  FUN_0004aaf6(DAT_1ffe0714,0x80,uVar7,uVar1);
  return;
}

