/* Address: 00056244; name: FUN_00056244; body bytes: 532 */

void FUN_00056244(void)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  if (DAT_1ffe0620 == 0) {
    return;
  }
  iVar1 = FUN_0004cd1e(DAT_1ffe0654);
  if (iVar1 != 0) {
    if (DAT_1fffaae5 != '\t') {
      return;
    }
    iVar1 = get_output_enabled();
    if (iVar1 == 0) {
      return;
    }
    FUN_0001ba58();
    DAT_1fffaad3 = 0;
    FUN_0001814c();
    FUN_0005651c(0);
    uVar2 = FUN_00037604();
    FUN_0004eb0e(DAT_1ffe0680,uVar2);
    FUN_0004eb0e(DAT_1ffe0654,0);
    return;
  }
  uVar3 = (DAT_1fffab80 + 0x32) / 100;
  uVar5 = (DAT_1fffaba4 + 0x32) / 100;
  uVar4 = (DAT_1fffaba8 + 5U) / 10;
  FUN_00049974(DAT_1ffe0668,(&DAT_1ffe07bc)[DAT_1fffab46]);
  if (DAT_1fffab46 == 5) {
    FUN_000499de(DAT_1ffe066c,&DAT_00056448);
  }
  else {
    FUN_000499de(DAT_1ffe066c,&DAT_00056444,DAT_1fffab45);
  }
  FUN_000499de(DAT_1ffe0658,"%d.%01d",uVar3 / 10,uVar3 % 10);
  if (DAT_1fffaba4 < 1000) {
    FUN_00049974(DAT_1ffe0660,&DAT_00056460);
    uVar5 = DAT_1fffaba4;
  }
  else {
    if (DAT_1fffaba4 - 1000 < 99000) {
      FUN_00049974(DAT_1ffe0660,&DAT_00056468);
      FUN_000499de(DAT_1ffe065c,"%02d.%01d",uVar5 / 10,uVar5 % 10);
      goto LAB_00056346;
    }
    FUN_00049974(DAT_1ffe0660,&DAT_00056468);
    uVar5 = uVar5 / 10;
  }
  FUN_000499de(DAT_1ffe065c,&DAT_00056478,uVar5);
LAB_00056346:
  FUN_000499de(DAT_1ffe0670,"%02d.%02d",DAT_1fffab7e / 100,(uint)DAT_1fffab7e % 100);
  FUN_000499de(DAT_1ffe0674,"%03d.%02d",uVar4 / 100,uVar4 % 100);
  FUN_000499de(DAT_1ffe0678,"%03d.%02d",DAT_1fffab82 / 100,(uint)DAT_1fffab82 % 100);
  FUN_000499de(DAT_1ffe067c,"%02d:%02d:%02d",DAT_1fffabac / 0xe10,(DAT_1fffabac % 0xe10) / 0x3c);
  if ((4 < DAT_1fffab47) && (DAT_1fffab44 != '\x01')) {
    FUN_0005651c(1);
    DAT_1fffab44 = '\x01';
    FUN_0001cb8c(8);
  }
  if (DAT_1fffab47 != 0) {
    return;
  }
  DAT_1fffac98 = DAT_1fffab46;
  DAT_1fffac99 = DAT_1fffab45;
  DAT_1fffac9c = DAT_1fffaba4;
  DAT_1fffaca0 = DAT_1fffaba8;
  DAT_1fffaca4 = DAT_1fffabac;
  FUN_000380ec();
  FUN_0001d858();
  return;
}

