/* Address: 0001515c; name: FUN_0001515c; body bytes: 18 */

void FUN_0001515c(uint param_1,int param_2)

{
  if (param_2 == 1) {
    DAT_40048000 = DAT_40048000 & ~param_1;
  }
  else {
    DAT_40048000 = DAT_40048000 | param_1;
  }
  return;
}

