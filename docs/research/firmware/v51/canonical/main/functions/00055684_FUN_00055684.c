/* Address: 00055684; name: FUN_00055684; body bytes: 68 */

void FUN_00055684(uint param_1)

{
  char *pcVar1;
  
  if (DAT_1ffe05b8 != 0) {
    if (DAT_1ffe027a != param_1) {
      if (DAT_1fffaafb == '\0') {
        pcVar1 = "%01d.%03d A";
      }
      else {
        pcVar1 = "%01d.%03d    A";
      }
      FUN_000499de(DAT_1ffe05c0,pcVar1,param_1 / 1000,param_1 % 1000);
      DAT_1ffe027a = (ushort)param_1;
    }
    return;
  }
  DAT_1ffe027a = 0xffff;
  return;
}

