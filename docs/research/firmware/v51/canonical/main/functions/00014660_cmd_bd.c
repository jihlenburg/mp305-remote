/* Address: 00014660; name: cmd_bd; body bytes: 80 */

void cmd_bd(int param_1,int param_2,int param_3)

{
  if (param_3 == 6) {
    DAT_1fffaacf = *(char *)(param_1 + 1);
    if (DAT_1fffaacf == '\0') {
      DAT_1ffe0186 = 0;
      DAT_1ffe0196 = 0;
    }
  }
  else if (param_3 == 5) {
    DAT_1fffaad0 = *(char *)(param_1 + 1);
    FUN_0001046a(&DAT_1fffab24,param_1 + 2,param_2 + -2);
    (&DAT_1fffab22)[param_2] = 0;
  }
  if (DAT_1fffaad0 == '\0') {
    DAT_1ffe0191 = 2;
    DAT_1ffe01b0 = 0;
    DAT_1ffe0192 = 0;
    DAT_1ffe0193 = 0;
    DAT_1fffaae9 = 0;
    DAT_1fffaaea = 0;
  }
  return;
}

