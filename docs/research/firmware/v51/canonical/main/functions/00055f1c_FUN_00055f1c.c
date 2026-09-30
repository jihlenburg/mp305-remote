/* Address: 00055f1c; name: FUN_00055f1c; body bytes: 466 */

void FUN_00055f1c(void)

{
  undefined4 uVar1;
  int iVar2;
  
  if ((DAT_1fffab03 == '\0') || (DAT_1fffaad6 == '\0')) {
    if ((DAT_1fffab04 == '\0') || (DAT_1fffaad7 == '\0')) {
      FUN_0004e00e(DAT_1ffe03e0,1);
      FUN_0004aa6e(DAT_1ffe041c,1);
      uVar1 = FUN_0004b9de(DAT_1ffe044c,0);
      FUN_00047d8e(uVar1,&DAT_0007c788);
      FUN_0004e00e(DAT_1ffe03d4,1);
      FUN_000499de(DAT_1ffe03d4,&LAB_0005611c);
      FUN_0004aa6e(DAT_1ffe03d8,1);
      FUN_000178a4();
      FUN_0001814c();
    }
    else {
      FUN_0004aa6e(DAT_1ffe03e0,1);
      FUN_0004e00e(DAT_1ffe041c,1);
      uVar1 = FUN_0004b9de(DAT_1ffe044c,0);
      FUN_00047d8e(uVar1,&DAT_0007b924);
      FUN_0004aa6e(DAT_1ffe03d4,1);
      FUN_0004e00e(DAT_1ffe03d8,1);
      FUN_000507ca(DAT_1ffe03d8,0,0x13ec);
      FUN_0005075c(DAT_1ffe03d8,4,1);
      FUN_00050714(DAT_1ffe03d8,DAT_1fffaae3);
      FUN_000507e6(DAT_1ffe03d8,DAT_1fffab76);
      FUN_0004b9de(DAT_1ffe0420,1);
      iVar2 = FUN_0004ccf8();
      FUN_0004eae2(DAT_1ffe0424,(int)((uint)DAT_1fffab76 * (iVar2 + -4)) / 0x13ec);
      FUN_00057064(DAT_1fffaae4,1);
      FUN_00018114(DAT_1ffe03d8);
      if ((int)((uint)DAT_1fffaae4 << 0x1e) < 0) {
        FUN_0004e00e(DAT_1ffe0448,1);
        goto LAB_0005608e;
      }
    }
  }
  else {
    FUN_0004aa6e(DAT_1ffe03e0,1);
    FUN_0004e00e(DAT_1ffe041c,1);
    uVar1 = FUN_0004b9de(DAT_1ffe044c,0);
    FUN_00047d8e(uVar1,&DAT_0007b924);
    FUN_0004aa6e(DAT_1ffe03d4,1);
    FUN_0004e00e(DAT_1ffe03d8,1);
    FUN_000507ca(DAT_1ffe03d8,0,0xbea);
    FUN_0005075c(DAT_1ffe03d8,4,2);
    FUN_00050714(DAT_1ffe03d8,DAT_1fffaae2);
    FUN_000507e6(DAT_1ffe03d8,DAT_1fffab74);
    FUN_0004b9de(DAT_1ffe0420,1);
    iVar2 = FUN_0004ccf8();
    FUN_0004eae2(DAT_1ffe0424,(int)((uint)DAT_1fffab74 * (iVar2 + -4)) / 0xbea);
    FUN_00057064(DAT_1fffaae4,1);
    FUN_00018114(DAT_1ffe03d8);
  }
  FUN_0004aa6e(DAT_1ffe0448,1);
LAB_0005608e:
  uVar1 = FUN_0004b9de(DAT_1ffe0448,0);
  FUN_0004aa6e(uVar1,1);
  uVar1 = FUN_0004b9de(DAT_1ffe0448,1);
  FUN_0004aa6e(uVar1,1);
  return;
}

