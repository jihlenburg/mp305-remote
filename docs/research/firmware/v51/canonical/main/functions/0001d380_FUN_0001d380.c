/* Address: 0001d380; name: FUN_0001d380; body bytes: 382 */

void FUN_0001d380(void)

{
  int iVar1;
  
  if (DAT_1ffe01cc == '\0') {
    if (DAT_1fffa8cd != '\0') {
      iVar1 = FUN_00015bd0();
      if (DAT_1fffa350 != iVar1) {
        DAT_1fffa350 = iVar1;
        FUN_0001bdf6(0x160000);
        FUN_0001bf3a(0x160000,&DAT_1fffa138,0x21c);
      }
      iVar1 = FUN_000159cc();
      if (DAT_1fffa410 != iVar1) {
        DAT_1fffa410 = FUN_000159cc();
        FUN_0001bdf6(0x161000);
        FUN_0001bf3a(0x161000,&DAT_1fffa354,0xc0);
      }
      DAT_1fffa8cd = '\0';
    }
  }
  else {
    FUN_000188e0();
    FUN_00014318();
    DAT_1ffe01cc = '\0';
  }
  if (DAT_1fffa8ca != '\0') {
    DAT_1fffa8ca = '\0';
    FUN_0001bef8((uint)DAT_1ffe0188 * 0x1000 + 0x162000,&DAT_1fff8f7c,0x4b0);
    DAT_1fff9550 = DAT_1fff9550 | 0x80;
  }
  if (DAT_1fffa8c4 != '\0') {
    DAT_1fffa8c4 = '\0';
    DAT_1fffa350 = FUN_00015bd0();
    FUN_0001bdf6(0x160000);
    FUN_0001bf3a(0x160000,&DAT_1fffa138,0x21c);
    DAT_1fffaaf2 = 1;
    DAT_1fffab17 = 0;
  }
  if (DAT_1fffa8c6 != '\0') {
    DAT_1fffa410 = FUN_000159cc();
    FUN_0001bdf6(0x161000);
    FUN_0001bf3a(0x161000,&DAT_1fffa354,0xc0);
    DAT_1fffaaee = 1;
    DAT_1fffa8c9 = DAT_1fffa8c6 == '\x01';
    if (!(bool)DAT_1fffa8c9) {
      DAT_1fffab17 = 0;
    }
    DAT_1fffa8c6 = '\0';
  }
  if (DAT_1fffa8c8 != '\0') {
    DAT_1fffa8c8 = '\0';
    FUN_0001bdf6((uint)DAT_1fffa8cb * 0x1000 + 0x162000);
    FUN_0001bf3a((uint)DAT_1fffa8cb * 0x1000 + 0x162000,&DAT_1fff8f7c,0x4b0);
    DAT_1fff9550 = DAT_1fff9550 | 0x100;
    if (DAT_1fffa8cb == DAT_1fffa408) {
      DAT_1fffaaf0 = DAT_1fffa408;
      DAT_1fffaaed = 0;
      DAT_1fffaaef = '\x01';
    }
    if (DAT_1fffa8c9 != '\0') {
      DAT_1fffa8c9 = '\0';
      DAT_1fffab17 = 0;
    }
  }
  if (DAT_1fffaaef != '\0') {
    DAT_1fffaaef = '\0';
    FUN_0001bef8((uint)DAT_1fffaaf0 * 0x1000 + 0x162000,&DAT_1fffa414,0x4b0);
    DAT_1fffaaed = 1;
  }
  return;
}

