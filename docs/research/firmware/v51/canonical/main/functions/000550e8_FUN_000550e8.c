/* Address: 000550e8; name: FUN_000550e8; body bytes: 82 */

void FUN_000550e8(uint param_1)

{
  if (DAT_1ffe034c == 0) {
    DAT_1ffe0284 = 0xffff;
  }
  else if (DAT_1ffe0284 != param_1) {
    FUN_000499de(DAT_1ffe0374,"%03d.%02d",param_1 / 100,param_1 % 100);
    FUN_000499de(DAT_1ffe0584,"%03d.%02d",param_1 / 100,param_1 % 100);
    DAT_1ffe0284 = (ushort)param_1;
  }
  return;
}

