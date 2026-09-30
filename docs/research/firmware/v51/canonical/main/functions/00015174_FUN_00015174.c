/* Address: 00015174; name: FUN_00015174; body bytes: 18 */

void FUN_00015174(uint param_1,int param_2)

{
  if (param_2 == 1) {
    DAT_40048004 = DAT_40048004 & ~param_1;
  }
  else {
    DAT_40048004 = DAT_40048004 | param_1;
  }
  return;
}

