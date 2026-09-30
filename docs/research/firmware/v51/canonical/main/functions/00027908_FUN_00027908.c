/* Address: 00027908; name: FUN_00027908; body bytes: 70 */

/* Recovered from stored Thumb pointer at 0002275c; callback identification is inferred until
   reviewed. */

void FUN_00027908(void)

{
  undefined4 uVar1;
  
  DAT_1ffe024c = DAT_1ffe024c + 1;
  if ((7 < DAT_1ffe024c) && (DAT_1fffaad9 == '\0')) {
    DAT_1fffaad9 = 1;
    DAT_1ffe024c = 0;
    DAT_1fffa130 = 1000000;
    FUN_0001ae8c();
    uVar1 = FUN_0004b9de(DAT_1ffe0448,0);
    FUN_0004e00e(uVar1,1);
    FUN_0001cb8c(0xf);
    return;
  }
  return;
}

