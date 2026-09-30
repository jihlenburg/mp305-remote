/* Address: CODE:960e; name: FUN_CODE_960e; body bytes: 28 */

void FUN_CODE_960e(char *param_1,char param_2,char param_3)

{
  FUN_CODE_34c6();
  if (*param_1 == BANK0_R7) {
    FUN_CODE_34f1();
    if (*param_1 == BANK0_R5) {
      return;
    }
  }
  FUN_CODE_34c6();
  *param_1 = param_3;
  FUN_CODE_34f1();
  *param_1 = param_2;
  return;
}

