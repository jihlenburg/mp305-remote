/* Address: 0001f048; name: FUN_0001f048; body bytes: 74 */

/* Recovered from stored Thumb pointer at 00027dc0; callback identification is inferred until
   reviewed. */

void FUN_0001f048(void)

{
  char cVar1;
  
  cVar1 = FUN_0001f026(&DAT_40021000);
  if (DAT_1ffe0148 == '\0') {
    if (cVar1 == '\r') {
      (&DAT_1fff8a8c)[DAT_1ffe014c] = 0xd;
      DAT_1ffe014a = DAT_1ffe014c + 1;
      DAT_1ffe014c = 0;
      DAT_1ffe0148 = 1;
      return;
    }
    if (cVar1 != '\n') {
      if (0x1ff < DAT_1ffe014c) {
        DAT_1ffe014c = 0;
        DAT_1ffe014a = 0;
        return;
      }
      (&DAT_1fff8a8c)[DAT_1ffe014c] = cVar1;
      DAT_1ffe014c = DAT_1ffe014c + 1;
    }
  }
  return;
}

