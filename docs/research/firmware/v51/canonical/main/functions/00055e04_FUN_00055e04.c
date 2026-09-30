/* Address: 00055e04; name: FUN_00055e04; body bytes: 28 */

void FUN_00055e04(uint param_1)

{
  if (DAT_1ffe028e != param_1) {
    DAT_1ffe028e = (ushort)param_1;
    FUN_000499de(DAT_1ffe04dc,&DAT_00055e24,param_1);
    return;
  }
  return;
}

