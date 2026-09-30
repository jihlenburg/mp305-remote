/* Address: 0002e158; name: FUN_0002e158; body bytes: 574 */

void FUN_0002e158(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  DAT_1ffe0344 = FUN_000527d4();
  uVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe0344,uVar2,uVar1);
  FUN_0004ab24(DAT_1ffe0344,&DAT_1fffb940,0);
  uVar1 = FUN_0004029c();
  FUN_0004e8b2(DAT_1ffe0344,uVar1,0);
  FUN_0004e822(DAT_1ffe0344,0);
  DAT_1ffe0348 = FUN_00052740(DAT_1ffe0344,0,0,2);
  uVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe0348,uVar2,uVar1);
  FUN_0004ab24(DAT_1ffe0348,&DAT_1fffb940,0);
  uVar1 = FUN_0004029c();
  FUN_0004e8b2(DAT_1ffe0348,uVar1,0);
  FUN_0004e00e(DAT_1ffe0348,0x10);
  FUN_0004e822(DAT_1ffe0348,0);
  DAT_1ffe04f0 = FUN_00052740(DAT_1ffe0344,1,0);
  uVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe04f0,uVar2,uVar1);
  FUN_0004ab24(DAT_1ffe04f0,&DAT_1fffb940,0);
  uVar1 = FUN_0004029c();
  FUN_0004e8b2(DAT_1ffe04f0,uVar1,0);
  FUN_0004e00e(DAT_1ffe04f0,0x10);
  FUN_0004e822(DAT_1ffe04f0,0);
  FUN_00030e8c(DAT_1ffe04f0);
  DAT_1ffe03b8 = FUN_0004b384(DAT_1ffe04f0);
  uVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe03b8,uVar2,uVar1);
  FUN_0004e7c2(DAT_1ffe03b8,0);
  FUN_0004ab24(DAT_1ffe03b8,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe03b8,0);
  FUN_0004aa6e(DAT_1ffe03b8,1);
  uVar1 = FUN_00049a70();
  FUN_0004e00e(uVar1,0x10);
  FUN_00034bf0(uVar1);
  FUN_00032454(uVar1);
  FUN_000288a4(uVar1);
  FUN_000358d8(uVar1);
  FUN_000351c4(uVar1);
  FUN_0003030c(uVar1);
  FUN_0002840c(uVar1);
  FUN_000285d4(uVar1);
  FUN_0002ec4c(uVar1);
  DAT_1ffe03bc = FUN_0004b384(uVar1);
  uVar2 = FUN_000375f8();
  uVar3 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe03bc,uVar3,uVar2);
  FUN_0004e7c2(DAT_1ffe03bc,0);
  FUN_0004ab24(DAT_1ffe03bc,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe03bc,0);
  if (DAT_1fffaadb == '\0') {
    FUN_0004aa6e(DAT_1ffe03bc,1);
  }
  else {
    FUN_0004e00e();
  }
  DAT_1ffe03c4 = FUN_0004b384(uVar1);
  uVar1 = FUN_000375f8();
  uVar2 = FUN_00037604();
  FUN_0004e84a(DAT_1ffe03c4,uVar2,uVar1);
  FUN_0004e7c2(DAT_1ffe03c4,0);
  FUN_0004ab24(DAT_1ffe03c4,&DAT_1fffb940,0);
  FUN_0004e8dc(DAT_1ffe03c4,0);
  if (remote_granted == '\x01') {
    FUN_0004e00e(DAT_1ffe03c4,1);
  }
  else {
    FUN_0004aa6e();
  }
  if (current_mode == '\0') {
    FUN_000301e8();
  }
  else {
    if (current_mode == '\x01') {
      FUN_0002f6e4();
    }
    else if (current_mode == '\x02') {
      FUN_00033538();
    }
    else {
      FUN_0002aa74();
    }
    FUN_0004e00e(DAT_1ffe0344,0x10);
  }
  DAT_1ffe0330 = 0;
  return;
}

