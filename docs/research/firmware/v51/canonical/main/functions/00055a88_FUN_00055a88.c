/* Address: 00055a88; name: FUN_00055a88; body bytes: 28 */

void FUN_00055a88(uint param_1)

{
  if (DAT_1ffe0290 != param_1) {
    DAT_1ffe0290 = (ushort)param_1;
    FUN_000499de(DAT_1ffe04e8,&DAT_00055aa8,param_1);
    return;
  }
  return;
}

