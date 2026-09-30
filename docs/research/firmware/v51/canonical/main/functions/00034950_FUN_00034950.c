/* Address: 00034950; name: FUN_00034950; body bytes: 578 */

void FUN_00034950(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  DAT_1ffe0378 = FUN_00048d88();
  FUN_0004e84a(DAT_1ffe0378,0x56,0x10);
  FUN_0004e7c2(DAT_1ffe0378,0x90,2);
  FUN_0004ab24(DAT_1ffe0378,&DAT_1fffb940,0);
  FUN_0004ab24(DAT_1ffe0378,&DAT_1fffb9b8,0);
  FUN_0004eab0(DAT_1ffe0378,&DAT_0006a6dc,0);
  FUN_000499de(DAT_1ffe0378,&DAT_00034ba4);
  FUN_0004ea28(DAT_1ffe0378,4,0);
  DAT_1ffe037c = FUN_00048d88(param_1);
  FUN_0004e84a(DAT_1ffe037c,0x7c,0x1b);
  FUN_0004e7c2(DAT_1ffe037c,0x90,0x12);
  FUN_0004ab24(DAT_1ffe037c,&DAT_1fffb940,0);
  FUN_0004ab24(DAT_1ffe037c,&DAT_1fffb9dc,0);
  uVar1 = FUN_0004037c(0x333333);
  FUN_0004e8b2(DAT_1ffe037c,uVar1,0);
  FUN_0004ea3c(DAT_1ffe037c,2,0);
  FUN_0004ea28(DAT_1ffe037c,5,0);
  FUN_000499de(DAT_1ffe037c,"%03ld:%02ld:%02ld",DAT_1fffab9c / 0xe10,(DAT_1fffab9c % 0xe10) / 0x3c,
               (DAT_1fffab9c % 0xe10) % 0x3c);
  DAT_1ffe0380 = FUN_00048d88(param_1);
  FUN_0004e84a(DAT_1ffe0380,0x7c,0x1b);
  FUN_0004e7c2(DAT_1ffe0380,0x90,0x31);
  FUN_0004ab24(DAT_1ffe0380,&DAT_1fffb940,0);
  FUN_0004ab24(DAT_1ffe0380,&DAT_1fffb9dc,0);
  uVar1 = FUN_0004037c(0x333333);
  FUN_0004e8b2(DAT_1ffe0380,uVar1,0);
  FUN_0004ea3c(DAT_1ffe0380,2,0);
  FUN_0004ea28(DAT_1ffe0380,5,0);
  FUN_000499de(DAT_1ffe0380,"%03d.%01d",DAT_1fffaba0 / 10,DAT_1fffaba0 % 10);
  uVar1 = FUN_00048d88(DAT_1ffe0380);
  FUN_0004eae2(uVar1,0x3fffffff);
  FUN_0004ac0a(uVar1,7,0x37,0xffffffff);
  FUN_0004ab24(uVar1,&DAT_1fffb988,0);
  FUN_0004ea86(uVar1,2,0);
  FUN_000499de(uVar1,&DAT_00034bdc);
  DAT_1ffe0384 = FUN_00048d88(param_1);
  FUN_0004e84a(DAT_1ffe0384,0x56,0x10);
  FUN_0004e7c2(DAT_1ffe0384,0x90,0x4c);
  FUN_0004ab24(DAT_1ffe0384,&DAT_1fffb940,0);
  FUN_0004ab24(DAT_1ffe0384,&DAT_1fffb9b8,0);
  FUN_0004eab0(DAT_1ffe0384,&DAT_0006a6dc,0);
  FUN_000499de(DAT_1ffe0384,"ENERGY");
  FUN_0004ea28(DAT_1ffe0384,4,0);
  DAT_1ffe0388 = FUN_0003e808(param_1);
  FUN_0004e84a(DAT_1ffe0388,0x2e,0x3a);
  FUN_0004ac28(DAT_1ffe0388,DAT_1ffe037c,0x13,4);
  FUN_0004ab24(DAT_1ffe0388,&DAT_1fffb970,0);
  FUN_0004e8dc(DAT_1ffe0388,0);
  uVar1 = FUN_00047698(DAT_1ffe0388);
  FUN_0004b128();
  FUN_00047d8e(uVar1,&DAT_0007c3cc);
  FUN_0004e980(uVar1,0xff,0);
  uVar2 = FUN_0004037c(0xffffff);
  FUN_0004e960(uVar1,uVar2,0);
  FUN_0004aa6e(uVar1,2);
  FUN_0004aa6e(uVar1,0x4000);
  return;
}

