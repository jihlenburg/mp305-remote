/* Address: CODE:9ba3; name: FUN_CODE_9ba3; body bytes: 20 */

void FUN_CODE_9ba3(char *param_1,char param_2)

{
  if (param_2 == '\0') {
    FUN_CODE_44df(DAT_INTMEM_b3);
    *param_1 = '\0';
  }
  FUN_CODE_447d();
  *param_1 = param_2;
  DAT_INTMEM_cc = param_2;
  return;
}

