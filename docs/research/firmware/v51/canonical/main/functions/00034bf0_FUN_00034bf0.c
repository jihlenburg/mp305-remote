/* Address: 00034bf0; name: FUN_00034bf0; body bytes: 1416 */

void FUN_00034bf0(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined4 uVar4;
  
  DAT_1ffe0478 = FUN_0004b384();
  uVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe0478,uVar2,uVar1);
  uVar1 = FUN_00037604();
  FUN_0004e7c2(DAT_1ffe0478,uVar1,0);
  FUN_0004ab24(DAT_1ffe0478,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe0478,0);
  FUN_0004e822(DAT_1ffe0478,0);
  FUN_0004e00e(DAT_1ffe0478,0x10);
  DAT_1ffe047c = FUN_0004b384(DAT_1ffe0478);
  uVar1 = FUN_000375f8();
  FUN_0004e84a(DAT_1ffe047c,0x101,uVar1);
  FUN_0004ac0a(DAT_1ffe047c,3,0);
  FUN_0004ab24(DAT_1ffe047c,&DAT_1fffb958,0);
  DAT_1ffe0480 = FUN_0003e808(DAT_1ffe047c);
  FUN_0004e84a(DAT_1ffe0480,0x4d,0x75);
  FUN_0004ac0a(DAT_1ffe0480,6,0xfffffffe,0xfffffffe);
  FUN_0004ab24(DAT_1ffe0480,&DAT_1fffb94c,0);
  uVar1 = FUN_0004037c(0);
  FUN_0004e8e6(DAT_1ffe0480,uVar1,0);
  uVar1 = FUN_0004037c(0x999999);
  FUN_0004e8e6(DAT_1ffe0480,uVar1,0x80);
  FUN_0004e8dc(DAT_1ffe0480,0,0x80);
  FUN_0004e9f0(DAT_1ffe0480,0xfffffffa,4);
  DAT_1ffe0484 = FUN_00047698(DAT_1ffe0480);
  FUN_00047d8e(DAT_1ffe0484,&DAT_0007cb3c);
  FUN_0004ac0a(DAT_1ffe0484,2,0,0x1d);
  FUN_0004e980(DAT_1ffe0484,0xff,0);
  uVar1 = FUN_0004037c(0);
  FUN_0004e960(DAT_1ffe0484,uVar1,0);
  uVar1 = FUN_0004037c(0x999999);
  FUN_0004e960(DAT_1ffe0484,uVar1,0x80);
  DAT_1ffe0488 = FUN_00048d88(DAT_1ffe0480);
  FUN_0004ac0a(DAT_1ffe0488,2,0,0x45);
  uVar1 = FUN_00015a5c(8);
  FUN_000499de(DAT_1ffe0488,&DAT_0003500c,uVar1);
  FUN_0004eab0(DAT_1ffe0488,&DAT_0007a02c,0);
  uVar1 = FUN_0004037c(0);
  FUN_0004ea90(DAT_1ffe0488,uVar1,0);
  uVar1 = FUN_0004037c(0x999999);
  FUN_0004ea90(DAT_1ffe0488,uVar1,0x80);
  DAT_1ffe048c = FUN_0004b384(DAT_1ffe047c);
  FUN_0004e84a(DAT_1ffe048c,0xae,0x3a);
  FUN_0004ac0a(DAT_1ffe048c,0,2);
  FUN_0004ab24(DAT_1ffe048c,&DAT_1fffb958,0);
  FUN_0004ea60(DAT_1ffe048c,8,0);
  uVar2 = 0xffffff;
  uVar1 = 0;
  if (current_mode != '\0') {
    uVar1 = uVar2;
  }
  uVar1 = FUN_0004037c(uVar1);
  FUN_0004e8b2(DAT_1ffe048c,uVar1,0);
  FUN_0004aa6e(DAT_1ffe048c,2);
  FUN_0004e9f0(DAT_1ffe048c,0xfffffffa,4);
  DAT_1ffe0490 = FUN_00047698(DAT_1ffe048c);
  FUN_00047d8e(DAT_1ffe0490,&DAT_0007c628);
  FUN_0004ac0a(DAT_1ffe0490,7,0xb,0);
  FUN_0004e980(DAT_1ffe0490,0xff,0);
  uVar1 = FUN_0004037c(0xffffff);
  FUN_0004e960(DAT_1ffe0490,uVar1,0);
  DAT_1ffe0494 = FUN_00048d88(DAT_1ffe048c);
  FUN_0004ac0a(DAT_1ffe0494,7,0x35,0);
  uVar1 = FUN_00015a5c(2);
  FUN_000499de(DAT_1ffe0494,&DAT_0003500c,uVar1);
  FUN_0004eab0(DAT_1ffe0494,&DAT_0007a02c,0);
  uVar1 = FUN_0004037c(0xffffff);
  FUN_0004ea90(DAT_1ffe0494,uVar1,0);
  DAT_1ffe0498 = FUN_0004b384(DAT_1ffe047c);
  FUN_0004e84a(DAT_1ffe0498,0xae,0x3a);
  FUN_0004ac28(DAT_1ffe0498,DAT_1ffe048c,0xd,0,2);
  FUN_0004ab24(DAT_1ffe0498,&DAT_1fffb958,0);
  uVar1 = uVar2;
  if (current_mode == '\x01') {
    uVar1 = 0;
  }
  uVar1 = FUN_0004037c(uVar1);
  FUN_0004e8b2(DAT_1ffe0498,uVar1,0);
  FUN_0004aa6e(DAT_1ffe0498,2);
  FUN_0004e9f0(DAT_1ffe0498,0xfffffffa,4);
  DAT_1ffe049c = FUN_00047698(DAT_1ffe0498);
  FUN_00047d8e(DAT_1ffe049c,&DAT_0007c334);
  FUN_0004ac0a(DAT_1ffe049c,7,0xb,0);
  FUN_0004e980(DAT_1ffe049c,0xff,0);
  uVar1 = FUN_0004037c(0);
  FUN_0004e960(DAT_1ffe049c,uVar1,0);
  DAT_1ffe04a0 = FUN_00048d88(DAT_1ffe0498);
  FUN_0004ac0a(DAT_1ffe04a0,7,0x35,0);
  uVar1 = FUN_00015a5c(3);
  FUN_000499de(DAT_1ffe04a0,&DAT_0003500c,uVar1);
  FUN_0004eab0(DAT_1ffe04a0,&DAT_0007a02c,0);
  uVar1 = FUN_0004037c(0);
  FUN_0004ea90(DAT_1ffe04a0,uVar1,0);
  DAT_1ffe04a4 = FUN_0004b384(DAT_1ffe047c);
  FUN_0004e84a(DAT_1ffe04a4,0xae,0x3a);
  uVar4 = 2;
  FUN_0004ac28(DAT_1ffe04a4,DAT_1ffe0498,0xd,0);
  FUN_0004ab24(DAT_1ffe04a4,&DAT_1fffb958,0);
  uVar1 = uVar2;
  if (current_mode == '\x02') {
    uVar1 = 0;
  }
  uVar1 = FUN_0004037c(uVar1);
  FUN_0004e8b2(DAT_1ffe04a4,uVar1,0);
  FUN_0004aa6e(DAT_1ffe04a4,2);
  FUN_0004e9f0(DAT_1ffe04a4,0xfffffffa,4);
  DAT_1ffe04a8 = FUN_00047698(DAT_1ffe04a4);
  FUN_00047d8e(DAT_1ffe04a8,&DAT_0007d934);
  FUN_0004ac0a(DAT_1ffe04a8,7,0xb,0);
  FUN_0004e980(DAT_1ffe04a8,0xff,0);
  uVar1 = FUN_0004037c(0);
  FUN_0004e960(DAT_1ffe04a8,uVar1,0);
  DAT_1ffe04ac = FUN_00048d88(DAT_1ffe04a4);
  FUN_0004ac0a(DAT_1ffe04ac,7,0x35,0);
  uVar1 = FUN_00015a5c(4);
  FUN_000499de(DAT_1ffe04ac,&DAT_0003500c,uVar1);
  FUN_0004eab0(DAT_1ffe04ac,&DAT_0007a02c,0);
  uVar1 = FUN_0004037c(0);
  FUN_0004ea90(DAT_1ffe04ac,uVar1,0);
  DAT_1ffe04b0 = FUN_0004b384(DAT_1ffe047c);
  FUN_0004e84a(DAT_1ffe04b0,0xae,0x3a);
  FUN_0004ac0a(DAT_1ffe04b0,4,2,0xfffffffe);
  FUN_0004ab24(DAT_1ffe04b0,&DAT_1fffb958,0);
  uVar1 = uVar2;
  if (current_mode == '\x03') {
    uVar1 = 0;
  }
  uVar1 = FUN_0004037c(uVar1);
  FUN_0004e8b2(DAT_1ffe04b0,uVar1,0);
  FUN_0004aa6e(DAT_1ffe04b0,2);
  FUN_0004e9f0(DAT_1ffe04b0,0xfffffffa,4);
  DAT_1ffe04b4 = FUN_00047698(DAT_1ffe04b0);
  FUN_00047d8e(DAT_1ffe04b4,&DAT_0008194c);
  FUN_0004ac0a(DAT_1ffe04b4,7,0xb,0);
  FUN_0004e980(DAT_1ffe04b4,0xff,0);
  uVar1 = FUN_0004037c(0);
  FUN_0004e960(DAT_1ffe04b4,uVar1,0);
  DAT_1ffe04b8 = FUN_00048d88(DAT_1ffe04b0);
  FUN_0004ac0a(DAT_1ffe04b8,7,0x35,0);
  uVar1 = FUN_00015a5c(5);
  FUN_000499de(DAT_1ffe04b8,&DAT_0003500c,uVar1);
  FUN_0004eab0(DAT_1ffe04b8,&DAT_0007a02c,0);
  uVar1 = FUN_0004037c(0);
  FUN_0004ea90(DAT_1ffe04b8,uVar1,0);
  DAT_1ffe04bc = FUN_0003e808(DAT_1ffe047c);
  FUN_0004e84a(DAT_1ffe04bc,0x4d,0x75);
  FUN_0004ac0a(DAT_1ffe04bc,3,0xfffffffe,2);
  FUN_0004ab24(DAT_1ffe04bc,&DAT_1fffb94c,0);
  uVar1 = FUN_0004037c(0);
  FUN_0004e8e6(DAT_1ffe04bc,uVar1,0);
  FUN_0004e9f0(DAT_1ffe04bc,0xfffffffa,4);
  uVar1 = uVar2;
  if (DAT_1fffaadb != '\0') {
    uVar1 = 0xff0004;
  }
  uVar1 = FUN_0004037c(uVar1);
  FUN_0004e8b2(DAT_1ffe04bc,uVar1,0);
  DAT_1ffe04c0 = FUN_00047698(DAT_1ffe04bc);
  if (DAT_1fffaadb == '\0') {
    puVar3 = &DAT_0007b73c;
  }
  else {
    puVar3 = &DAT_0007b4c0;
  }
  FUN_00047d8e(DAT_1ffe04c0,puVar3);
  FUN_0004ac0a(DAT_1ffe04c0,2,0,0x1d);
  uVar1 = 0;
  if (DAT_1fffaadb != '\0') {
    uVar1 = uVar2;
  }
  uVar1 = FUN_0004037c(uVar1);
  FUN_0004e960(DAT_1ffe04c0,uVar1,0);
  DAT_1ffe04c4 = FUN_00048d88(DAT_1ffe04bc);
  FUN_0004ac0a(DAT_1ffe04c4,2,0,0x45);
  if (DAT_1fffaadb == '\0') {
    uVar1 = 6;
  }
  else {
    uVar1 = 7;
  }
  uVar1 = FUN_00015a5c(uVar1);
  FUN_000499de(DAT_1ffe04c4,&DAT_0003500c,uVar1);
  FUN_0004eab0(DAT_1ffe04c4,&DAT_0007a02c,0);
  uVar1 = 0;
  if (DAT_1fffaadb != '\0') {
    uVar1 = uVar2;
  }
  uVar1 = FUN_0004037c(uVar1);
  FUN_0004ea90(DAT_1ffe04c4,uVar1,0,uVar4);
  return;
}

