/* Address: 00056e14; name: FUN_00056e14; body bytes: 24 */

void FUN_00056e14(uint param_1)

{
  if (DAT_1ffe026e != param_1) {
    DAT_1ffe026e = (ushort)param_1;
    FUN_000499de(DAT_1ffe0598,&DAT_00056e30,param_1);
    return;
  }
  return;
}

