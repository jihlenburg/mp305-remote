/* Address: 0001518c; name: FUN_0001518c; body bytes: 18 */

void FUN_0001518c(uint param_1,int param_2)

{
  if (param_2 == 1) {
    DAT_40048008 = DAT_40048008 & ~param_1;
  }
  else {
    DAT_40048008 = DAT_40048008 | param_1;
  }
  return;
}

