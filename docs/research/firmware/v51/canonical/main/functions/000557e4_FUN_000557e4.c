/* Address: 000557e4; name: FUN_000557e4; body bytes: 66 */

void FUN_000557e4(uint param_1)

{
  char *pcVar1;
  
  if (DAT_1ffe05b8 != 0) {
    if (DAT_1ffe0274 != param_1) {
      if (DAT_1fffaafb == '\0') {
        pcVar1 = "%02d.%02d V";
      }
      else {
        pcVar1 = "%02d.%02d    V";
      }
      FUN_000499de(DAT_1ffe05bc,pcVar1,param_1 / 100,param_1 % 100);
      DAT_1ffe0274 = (ushort)param_1;
    }
    return;
  }
  DAT_1ffe0274 = 0xffff;
  return;
}

