/* Address: 00055a54; name: FUN_00055a54; body bytes: 30 */

void FUN_00055a54(uint param_1)

{
  if (DAT_1ffe0264 != param_1) {
    DAT_1ffe0264 = (byte)param_1;
    FUN_000499de(DAT_1ffe04ec,&DAT_00055a7c,(&DAT_1ffe0778)[param_1]);
    return;
  }
  return;
}

