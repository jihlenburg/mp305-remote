/* Address: 00054fd8; name: FUN_00054fd8; body bytes: 76 */

void FUN_00054fd8(uint param_1)

{
  if (DAT_1ffe034c == 0) {
    DAT_1ffe02d0 = 0xffffffff;
  }
  else if (DAT_1ffe02d0 != param_1) {
    FUN_000499de(DAT_1ffe0380,"%03d.%01d",param_1 / 10,param_1 % 10);
    FUN_000499de(DAT_1ffe058c,"%03d.%01d",param_1 / 10,param_1 % 10);
    DAT_1ffe02d0 = param_1;
  }
  return;
}

