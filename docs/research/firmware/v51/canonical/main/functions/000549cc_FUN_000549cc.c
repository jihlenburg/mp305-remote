/* Address: 000549cc; name: FUN_000549cc; body bytes: 56 */

void FUN_000549cc(uint param_1)

{
  if (DAT_1ffe024f != param_1) {
    DAT_1ffe024f = (byte)param_1;
    FUN_000499de(DAT_1ffe0594,&DAT_00054a08,param_1);
    FUN_0004eae2(DAT_1ffe059c,((short)(100 - (short)param_1) * 0x32) / 100);
    return;
  }
  return;
}

