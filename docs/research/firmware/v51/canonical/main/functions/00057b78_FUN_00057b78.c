/* Address: 00057b78; name: FUN_00057b78; body bytes: 134 */

void FUN_00057b78(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  undefined1 auStack_28 [20];
  
  if (DAT_1fffaaf2 != '\0' || param_1 != 0) {
    if (DAT_1ffe05b8 != 0) {
      uVar2 = 0;
      do {
        FUN_0001046a(auStack_28,&DAT_1fffa138 + uVar2 * 0x10,0x10);
        uVar1 = FUN_0004b9de(DAT_1ffe0610,uVar2);
        uVar1 = FUN_0004b9de(uVar1,1);
        FUN_000499de(uVar1,&DAT_00057c10,auStack_28);
        uVar1 = FUN_0004b9de(DAT_1ffe0610,uVar2);
        uVar1 = FUN_0004b9de(uVar1,2);
        FUN_000499de(uVar1,&LAB_00057c14,(&DAT_1fffa340)[uVar2]);
        uVar2 = uVar2 + 1 & 0xff;
      } while (uVar2 < 10);
      uVar1 = FUN_0004b9de(DAT_1ffe0610,DAT_1fffa34a);
      FUN_0004e4b2(uVar1,0);
      if (DAT_1fffaaf2 != '\0') {
        FUN_0005735c(0);
      }
    }
    DAT_1fffaaf2 = '\0';
  }
  return;
}

