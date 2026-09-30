/* Address: 00055e30; name: FUN_00055e30; body bytes: 66 */

void FUN_00055e30(uint param_1)

{
  if (DAT_1ffe02d8 == param_1) {
    return;
  }
  DAT_1ffe02d8 = param_1;
  if (param_1 != 0xffffffff) {
    FUN_000499de(DAT_1ffe04e0,"%ldh%02ldmin",param_1 / 0xe10,(param_1 % 0xe10) / 0x3c);
    return;
  }
  FUN_000499de(DAT_1ffe04e0,&DAT_00055e8c);
  return;
}

