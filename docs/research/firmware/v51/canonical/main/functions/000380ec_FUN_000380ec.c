/* Address: 000380ec; name: FUN_000380ec; body bytes: 284 */

void FUN_000380ec(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 extraout_r3;
  undefined4 unaff_r4;
  uint uVar4;
  uint uVar5;
  
  DAT_1ffe0249 = 0;
  uVar1 = FUN_00037604();
  FUN_0004eb0e(DAT_1ffe0654,uVar1);
  FUN_00018114(DAT_1ffe0348);
  uVar4 = (DAT_1fffaca0 + 5U) / 10;
  if (DAT_1fffac98 == 5) {
    uVar1 = FUN_0004b9de(DAT_1ffe0688,0);
    uVar1 = FUN_0004b9de(uVar1,0);
    FUN_000499de(uVar1,&DAT_00056c00,(&DAT_1ffe07bc)[DAT_1fffac98]);
  }
  else {
    uVar1 = extraout_r3;
    uVar2 = FUN_0004b9de(DAT_1ffe0688,0);
    uVar2 = FUN_0004b9de(uVar2,0);
    FUN_000499de(uVar2,"%s  %dS",(&DAT_1ffe07bc)[DAT_1fffac98],DAT_1fffac99,uVar1,unaff_r4);
  }
  uVar1 = FUN_0004b9de(DAT_1ffe0688,1);
  uVar1 = FUN_0004b9de(uVar1,0);
  FUN_000499de(uVar1,"%d  mAh",DAT_1fffac9c);
  uVar1 = FUN_0004b9de(DAT_1ffe0688,2);
  uVar1 = FUN_0004b9de(uVar1,0);
  FUN_000499de(uVar1,"%d.%02d  Wh",uVar4 / 100,uVar4 % 100);
  uVar4 = DAT_1fffaca4 % 0xe10;
  uVar3 = DAT_1fffaca4 % 0xe10;
  uVar5 = DAT_1fffaca4 / 0xe10;
  uVar1 = FUN_0004b9de(DAT_1ffe0688,3);
  uVar1 = FUN_0004b9de(uVar1,0);
  FUN_000499de(uVar1,"%02d:%02d:%02d",uVar5,uVar3 / 0x3c,uVar4 % 0x3c);
  if (DAT_1fffaacf != '\0') {
    DAT_1fff9550 = DAT_1fff9550 | 0x800;
  }
  return;
}

