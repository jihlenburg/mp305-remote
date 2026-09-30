/* Address: 000202cc; name: scatter_zero_bss; body bytes: 14 */

void scatter_zero_bss(undefined4 param_1,undefined4 *param_2,int param_3)

{
  for (; param_3 != 0; param_3 = param_3 + -4) {
    *param_2 = 0;
    param_2 = param_2 + 1;
  }
  return;
}

