/* Address: 00055774; name: FUN_00055774; body bytes: 78 */

void FUN_00055774(uint param_1)

{
  if (DAT_1ffe05b8 != 0) {
    if (DAT_1ffe02cc != param_1) {
      DAT_1ffe02cc = param_1;
      FUN_000499de(DAT_1ffe05cc,"%02ld:%02ld:%02ld",param_1 / 0xe10,(param_1 % 0xe10) / 0x3c,
                   (param_1 % 0xe10) % 0x3c);
    }
    return;
  }
  DAT_1ffe02cc = 0xffffffff;
  return;
}

