/* Address: 000151a4; name: FUN_000151a4; body bytes: 18 */

void FUN_000151a4(uint param_1,int param_2)

{
  if (param_2 == 1) {
    DAT_4004800c = DAT_4004800c & ~param_1;
  }
  else {
    DAT_4004800c = DAT_4004800c | param_1;
  }
  return;
}

