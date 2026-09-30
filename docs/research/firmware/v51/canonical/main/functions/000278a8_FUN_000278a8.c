/* Address: 000278a8; name: FUN_000278a8; body bytes: 76 */

void FUN_000278a8(void)

{
  undefined4 uVar1;
  
  if (DAT_1fffabb8 - 900000U < 0x30d41) {
    DAT_1fffa130 = DAT_1fffabb8;
    FUN_0001ae8c();
    FUN_0004aa6e(DAT_1ffe0448,1);
    uVar1 = FUN_0004b9de(DAT_1ffe0448,0);
    FUN_0004aa6e(uVar1,1);
    uVar1 = FUN_0004b9de(DAT_1ffe0448,1);
    FUN_0004aa6e(uVar1,1);
    FUN_0001cb8c(0xf);
    return;
  }
  return;
}

