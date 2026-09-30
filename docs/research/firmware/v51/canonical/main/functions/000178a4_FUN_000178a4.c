/* Address: 000178a4; name: FUN_000178a4; body bytes: 154 */

void FUN_000178a4(void)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (DAT_1ffe034c == 0) {
    return;
  }
  uVar2 = 0;
  if (DAT_1fffaad7 != '\0') {
    do {
      uVar1 = FUN_0004b9de(DAT_1ffe03e0,uVar2);
      FUN_0004e0e6(uVar1,0x80);
      uVar1 = FUN_0004b9de(DAT_1ffe03e0,uVar2);
      uVar1 = FUN_0004b9de(uVar1,0);
      FUN_0004e0e6(uVar1,0x80);
      while( true ) {
        uVar2 = uVar2 + 1 & 0xff;
        if (10 < uVar2) {
          return;
        }
        if (3 < uVar2 - 6) break;
        uVar1 = FUN_0004b9de(DAT_1ffe03e0,uVar2);
        FUN_0004aaf6(uVar1,0x80);
        uVar1 = FUN_0004b9de(DAT_1ffe03e0,uVar2);
        uVar1 = FUN_0004b9de(uVar1,0);
        FUN_0004aaf6(uVar1,0x80);
      }
    } while( true );
  }
  do {
    uVar1 = FUN_0004b9de(DAT_1ffe03e0,uVar2);
    FUN_0004e0e6(uVar1,0x80);
    uVar1 = FUN_0004b9de(DAT_1ffe03e0,uVar2);
    uVar1 = FUN_0004b9de(uVar1,0);
    FUN_0004e0e6(uVar1,0x80);
    uVar2 = uVar2 + 1 & 0xff;
  } while (uVar2 < 0xb);
  return;
}

