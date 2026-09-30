/* Address: 0002aa74; name: FUN_0002aa74; body bytes: 1870 */

void FUN_0002aa74(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 unaff_r4;
  uint uVar7;
  undefined4 unaff_r5;
  undefined4 unaff_r6;
  undefined4 uVar8;
  undefined4 unaff_r7;
  undefined4 unaff_r8;
  undefined4 unaff_lr;
  undefined8 uVar9;
  
  FUN_0004b288(DAT_1ffe0348);
  DAT_1ffe0620 = FUN_0004b384(DAT_1ffe0348);
  uVar2 = FUN_000375f8();
  uVar3 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe0620,uVar3,uVar2);
  FUN_0004e7c2(DAT_1ffe0620,0);
  FUN_0004ab24(DAT_1ffe0620,&DAT_1fffb940,0);
  uVar2 = FUN_0004029c();
  FUN_0004e8b2(DAT_1ffe0620,uVar2,0);
  FUN_0004e00e(DAT_1ffe0620,0x10);
  FUN_0004e822(DAT_1ffe0620,0);
  uVar2 = FUN_0004b384(DAT_1ffe0620);
  FUN_0004e84a(uVar2,0x8c,0x1e);
  FUN_0004ac0a(uVar2,1,2);
  FUN_0004ab24(uVar2,&DAT_1fffb940,0);
  uVar2 = FUN_00048d88(uVar2);
  FUN_0004ab24(uVar2,&DAT_1fffb9c4,0);
  uVar3 = FUN_00015a5c(0x4d);
  FUN_000499de(uVar2,&DAT_0002ae84,uVar3);
  FUN_0004b128(uVar2);
  uVar2 = FUN_0004b384(DAT_1ffe0620);
  iVar4 = FUN_00037604();
  FUN_0004e84a(uVar2,iVar4 + -4,2);
  FUN_0004ac0a(uVar2,2,0,0x1e);
  FUN_0004ab24(uVar2,&DAT_1fffb940,0);
  DAT_1ffe0624 = FUN_0004a0b8(DAT_1ffe0620);
  iVar4 = FUN_000375f8();
  iVar5 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe0624,iVar5 + -4,iVar4 + -0x20);
  FUN_0004ac0a(DAT_1ffe0624,5,0);
  FUN_0004ab24(DAT_1ffe0624,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe0624,0);
  FUN_0004e822(DAT_1ffe0624,0);
  uVar2 = FUN_00015a5c(0x48);
  uVar2 = FUN_0004a094(DAT_1ffe0624,uVar2);
  FUN_0004ab24(uVar2,&DAT_1fffba78,0);
  uVar3 = FUN_00047698(uVar2);
  FUN_00047d8e(uVar3,&DAT_000819e4);
  FUN_0004ac0a(uVar3,7,0xffffffe7,0);
  FUN_0004e980(uVar3,0xff,0);
  uVar8 = 0xffffff;
  uVar6 = FUN_0004037c(0xffffff);
  FUN_0004e960(uVar3,uVar6,0);
  uVar3 = FUN_00048d88(uVar2);
  FUN_0004ac0a(uVar3,3,0);
  FUN_0004ab24(uVar3,&DAT_1fffb994,0);
  FUN_000499de(uVar3,&DAT_0002ae84,(&DAT_1ffe07bc)[DAT_1fffa0c7]);
  FUN_0004aa6e(uVar2,2);
  uVar2 = FUN_00015a5c(0x4e);
  uVar2 = FUN_0004a094(DAT_1ffe0624,uVar2);
  FUN_0004ab24(uVar2,&DAT_1fffba78,0);
  uVar3 = FUN_00047698(uVar2);
  FUN_00047d8e(uVar3,&DAT_00081a7c);
  FUN_0004ac0a(uVar3,7,0xffffffe6,0);
  FUN_0004e980(uVar3,0xff,0);
  uVar6 = FUN_0004037c(0xffffff);
  FUN_0004e960(uVar3,uVar6,0);
  uVar3 = FUN_00048d88(uVar2);
  FUN_0004ac0a(uVar3,3,0);
  FUN_0004ab24(uVar3,&DAT_1fffb994,0);
  if (DAT_1fffa0c7 == 5) {
    FUN_000499de(uVar3,&DAT_0002b100,*(undefined2 *)(&DAT_1ffe084e + (uint)DAT_1ffe032d * 2));
  }
  else {
    uVar9 = FUN_00010a20((&DAT_1ffe07e0)[(uint)DAT_1fffa0c7 * 0xb + (uint)DAT_1ffe032d]);
    uVar9 = FUN_00010920((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),0,0x408f4000);
    FUN_000499de(uVar3,"%.2fV",(int)uVar9,(int)((ulonglong)uVar9 >> 0x20));
  }
  FUN_0004aa6e(uVar2,2);
  uVar2 = FUN_00015a5c(0x4f);
  uVar2 = FUN_0004a094(DAT_1ffe0624,uVar2);
  FUN_0004ab24(uVar2,&DAT_1fffba78,0);
  uVar3 = FUN_00047698(uVar2);
  FUN_00047d8e(uVar3,&DAT_000816f0);
  FUN_0004ac0a(uVar3,7,0xffffffe7,0);
  FUN_0004e980(uVar3,0xff,0);
  uVar6 = FUN_0004037c(0xffffff);
  FUN_0004e960(uVar3,uVar6,0);
  uVar3 = FUN_00048d88(uVar2);
  FUN_0004ac0a(uVar3,3,0);
  FUN_0004ab24(uVar3,&DAT_1fffb994,0);
  FUN_0004aa6e(uVar2,2);
  if (DAT_1fffa0c7 == 5) {
    uVar6 = FUN_00015a5c(0x54);
    FUN_000499de(uVar3,&DAT_0002ae84,uVar6);
    FUN_0004e00e(uVar2,2);
  }
  else {
    FUN_000499de(uVar3,&DAT_0002aeb4,(undefined1)DAT_1fffac90);
    FUN_0004aa6e(uVar2,2);
  }
  uVar2 = FUN_00015a5c(0x50);
  uVar2 = FUN_0004a094(DAT_1ffe0624,uVar2);
  FUN_0004ab24(uVar2,&DAT_1fffba78,0);
  uVar3 = FUN_00047698(uVar2);
  FUN_00047d8e(uVar3,&DAT_00081b14);
  FUN_0004ac0a(uVar3,7,0xffffffe7,0);
  FUN_0004e980(uVar3,0xff,0);
  uVar6 = FUN_0004037c(0xffffff);
  FUN_0004e960(uVar3,uVar6,0);
  uVar3 = FUN_00048d88(uVar2);
  FUN_0004ac0a(uVar3,3,0);
  FUN_0004ab24(uVar3,&DAT_1fffb994,0);
  uVar9 = FUN_00010a20((&DAT_1fffa0e8)[DAT_1fffa0c7]);
  uVar9 = FUN_00010920((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),0,0x408f4000);
  FUN_000499de(uVar3,"%.1fA",(int)uVar9,(int)((ulonglong)uVar9 >> 0x20));
  FUN_0004aa6e(uVar2,2);
  uVar2 = FUN_00015a5c(0x51);
  uVar2 = FUN_0004a094(DAT_1ffe0624,uVar2);
  FUN_0004ab24(uVar2,&DAT_1fffba78,0);
  uVar3 = FUN_00047698(uVar2);
  FUN_00047d8e(uVar3,&DAT_00082244);
  FUN_0004ac0a(uVar3,7,0xffffffe7,0);
  FUN_0004e980(uVar3,0xff,0);
  uVar6 = FUN_0004037c(0xffffff);
  FUN_0004e960(uVar3,uVar6,0);
  uVar3 = FUN_00048d88(uVar2);
  FUN_0004ac0a(uVar3,3,0);
  FUN_0004ab24(uVar3,&DAT_1fffb994,0);
  FUN_00049974(uVar3,&DAT_0002aec8);
  FUN_0004aa6e(uVar2,2);
  uVar2 = FUN_00015a5c(0x52);
  uVar2 = FUN_0004a094(DAT_1ffe0624,uVar2);
  FUN_0004ab24(uVar2,&DAT_1fffba78,0);
  uVar3 = FUN_00047698(uVar2);
  FUN_00047d8e(uVar3,&DAT_000823b4);
  FUN_0004ac0a(uVar3,7,0xffffffe7,0);
  FUN_0004e980(uVar3,0xff,0);
  uVar6 = FUN_0004037c(0xffffff);
  FUN_0004e960(uVar3,uVar6,0);
  uVar3 = FUN_00048d88(uVar2);
  FUN_0004ac0a(uVar3,3,0);
  FUN_0004ab24(uVar3,&DAT_1fffb994,0);
  FUN_00049974(uVar3,&DAT_0002aec8);
  FUN_0004e906(uVar2,0);
  FUN_0004aa6e(uVar2,2);
  DAT_1ffe0628 = FUN_0004b384(DAT_1ffe0620);
  iVar4 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe0628,uVar2,iVar4 + -0x20);
  FUN_0004e7c2(DAT_1ffe0628,0,0x20);
  FUN_0004ab24(DAT_1ffe0628,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe0628,0);
  FUN_0004aa6e(DAT_1ffe0628,1);
  FUN_0002b350(DAT_1ffe0620);
  FUN_0002b448(DAT_1ffe0620);
  FUN_0002a13c(DAT_1ffe0620);
  FUN_0002b5e0(DAT_1ffe0620);
  DAT_1ffe062c = FUN_0003e808(DAT_1ffe0620);
  FUN_0004e84a(DAT_1ffe062c,0x24,0x1e);
  FUN_0004ac0a(DAT_1ffe062c,3,0xfffffffc);
  FUN_0004ab24(DAT_1ffe062c,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe062c,0);
  uVar2 = FUN_00028700(DAT_1ffe062c);
  FUN_0004b128();
  FUN_0004aa6e(uVar2,2);
  FUN_0004aa6e(uVar2,0x4000);
  uVar3 = FUN_0004037c(0xffffff);
  uVar6 = FUN_0004b9de(uVar2,0);
  FUN_0004e960(uVar6,uVar3,0);
  if (DAT_1fffab06 < 0xb) {
    uVar3 = FUN_0004037c(0xff0000);
    uVar6 = FUN_0004b9de(uVar2,1);
    FUN_0004e8b2(uVar6,uVar3,0);
    uVar3 = FUN_0004037c(0xff0000);
    uVar6 = FUN_0004b9de(uVar2,2);
    FUN_0004e8e6(uVar6,uVar3,0);
    uVar8 = 0xff0000;
  }
  else {
    uVar3 = FUN_0004037c(0xffffff);
    uVar6 = FUN_0004b9de(uVar2,1);
    FUN_0004e8b2(uVar6,uVar3,0);
    uVar3 = FUN_0004037c(0xffffff);
    uVar6 = FUN_0004b9de(uVar2,2);
    FUN_0004e8e6(uVar6,uVar3,0);
  }
  uVar3 = FUN_0004037c(uVar8);
  uVar2 = FUN_0004b9de(uVar2,3);
  FUN_0004e8b2(uVar2,uVar3,0);
  FUN_0002a254(DAT_1ffe0620);
  FUN_0002c8c0(DAT_1ffe0620);
  for (uVar7 = 0; iVar4 = FUN_0004ba5c(DAT_1ffe0624), uVar7 < iVar4 - 2U; uVar7 = uVar7 + 1 & 0xff)
  {
    uVar2 = FUN_0004b9de(DAT_1ffe0620,uVar7 + 4);
    uVar3 = FUN_0004b9de(DAT_1ffe0624,uVar7);
    FUN_0004aa4c(uVar3,0x5f155,0,uVar2,unaff_r4,unaff_r5,unaff_r6,unaff_r7,unaff_r8,unaff_lr);
  }
  iVar4 = FUN_0004ba5c(DAT_1ffe0624);
  uVar2 = FUN_0004b9de(DAT_1ffe0624,iVar4 + -2);
  FUN_0004aa4c(uVar2,0x3bcc1,0,0,unaff_r4,unaff_r5,unaff_r6,unaff_r7,unaff_r8,unaff_lr);
  iVar4 = FUN_0004ba5c(DAT_1ffe0624);
  uVar2 = FUN_0004b9de(DAT_1ffe0624,iVar4 + -1);
  FUN_0004aa4c(uVar2,0x60541,0);
  FUN_0004aa4c(DAT_1ffe0684,0x27509,7,0);
  for (uVar7 = 0; uVar1 = FUN_0004ba5c(DAT_1ffe0638), uVar7 < uVar1; uVar7 = uVar7 + 1 & 0xff) {
    uVar2 = FUN_0004b9de(DAT_1ffe0638,uVar7);
    FUN_0004aa4c(uVar2,0x26595,0);
  }
  for (uVar7 = 0; uVar1 = FUN_0004ba5c(DAT_1ffe0640), uVar7 < uVar1; uVar7 = uVar7 + 1 & 0xff) {
    uVar2 = FUN_0004b9de(DAT_1ffe0640,uVar7);
    FUN_0004aa4c(uVar2,0x26595,0);
  }
  for (uVar7 = 0; uVar1 = FUN_0004ba5c(DAT_1ffe0648), uVar7 < uVar1; uVar7 = uVar7 + 1 & 0xff) {
    uVar2 = FUN_0004b9de(DAT_1ffe0648,uVar7);
    FUN_0004aa4c(uVar2,0x26595,0);
  }
  for (uVar7 = 0; uVar1 = FUN_0004ba5c(DAT_1ffe0650), uVar7 < uVar1; uVar7 = uVar7 + 1 & 0xff) {
    uVar2 = FUN_0004b9de(DAT_1ffe0650,uVar7);
    FUN_0004aa4c(uVar2,0x26595,0);
  }
  FUN_0004aa4c(DAT_1ffe062c,0x246c9,7,0);
  FUN_0004aa4c(DAT_1ffe0630,0x246c9,7,0);
  return;
}

