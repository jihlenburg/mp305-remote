/* Address: 00019a50; name: FUN_00019a50; body bytes: 170 */

void FUN_00019a50(int param_1)

{
  if (5 < DAT_1fffaa54) {
    if (DAT_1fffa968 < 1) {
      DAT_1fffa974 = 0;
    }
    else {
      DAT_1fffa974 = (DAT_1fffa968 / 1000) * DAT_1fffa964;
    }
    if ((((DAT_1fffaa54 == 7) || (DAT_1fffaa54 == 8)) && (DAT_1fffaa2f != '\0')) && (param_1 != 0))
    {
      DAT_1fffa980 = DAT_1fffa980 + param_1;
      DAT_1ffe01e8 = ((DAT_1fffa968 + 500) / 1000) * param_1 + DAT_1ffe01e8;
      DAT_1ffe01e4 = ((DAT_1fffa974 + 500U) / 1000) * param_1 + DAT_1ffe01e4;
      if (3600000 < DAT_1ffe01e4) {
        DAT_1fffa978 = DAT_1ffe01e4 / 3600000 + DAT_1fffa978;
        DAT_1ffe01e4 = DAT_1ffe01e4 % 3600000;
      }
      if (3600000 < DAT_1ffe01e8) {
        DAT_1fffa97c = DAT_1ffe01e8 / 3600000 + DAT_1fffa97c;
        DAT_1ffe01e8 = DAT_1ffe01e8 % 3600000;
      }
      if (0xd693a018 < DAT_1fffa980) {
        DAT_1fffa980 = 0xd693a018;
      }
      if (0xf41dc < DAT_1fffa978) {
        DAT_1fffa978 = 0xf41dc;
      }
    }
  }
  return;
}

