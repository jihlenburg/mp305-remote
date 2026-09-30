/* Address: 00055630; name: FUN_00055630; body bytes: 54 */

void FUN_00055630(uint param_1)

{
  if (DAT_1ffe05b8 != 0) {
    if (DAT_1ffe02d4 != param_1) {
      FUN_000499de(DAT_1ffe05c8,"%03d.%01d Wh",param_1 / 10,param_1 % 10);
      DAT_1ffe02d4 = param_1;
    }
    return;
  }
  DAT_1ffe02d4 = 0xffffffff;
  return;
}

