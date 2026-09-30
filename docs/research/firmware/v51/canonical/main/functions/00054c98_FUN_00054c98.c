/* Address: 00054c98; name: FUN_00054c98; body bytes: 60 */

void FUN_00054c98(uint param_1)

{
  if (DAT_1ffe04f4 != 0) {
    if (DAT_1ffe0286 != param_1) {
      FUN_000499de(DAT_1ffe0518,"%03d.%02d",param_1 / 100,param_1 % 100);
      DAT_1ffe0286 = (ushort)param_1;
    }
    return;
  }
  DAT_1ffe0286 = 0xffff;
  return;
}

