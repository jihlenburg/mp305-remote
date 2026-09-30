/* Address: CODE:8e81; name: FUN_CODE_8e81; body bytes: 38 */

void FUN_CODE_8e81(char *param_1,char param_2)

{
  FUN_CODE_50e1();
  if (*param_1 != '\0') {
    FUN_CODE_a6fd();
    if (param_2 == '\x01') {
      FUN_CODE_5078();
      if (*param_1 != '\x02') {
        return;
      }
    }
    else {
      FUN_CODE_5085();
      if (*param_1 != '\x02') {
        return;
      }
    }
    _1_5 = 1;
    FUN_CODE_9cca();
    FUN_CODE_a6b5();
  }
  return;
}

