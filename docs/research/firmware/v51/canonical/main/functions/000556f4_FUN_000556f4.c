/* Address: 000556f4; name: FUN_000556f4; body bytes: 82 */

void FUN_000556f4(uint param_1)

{
  char *pcVar1;
  
  if (DAT_1ffe05b8 != 0) {
    if (DAT_1ffe0288 != param_1) {
      if (DAT_1fffaafb == '\0') {
        pcVar1 = "%03d.%01d W";
      }
      else {
        pcVar1 = "%03d.%01d   W";
      }
      FUN_000499de(DAT_1ffe05c4,pcVar1,param_1 / 100,(param_1 / 10) % 10);
      DAT_1ffe0288 = (ushort)param_1;
    }
    return;
  }
  DAT_1ffe0288 = 0xffff;
  return;
}

