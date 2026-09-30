/* Address: CODE:aefd; name: FUN_CODE_aefd; body bytes: 44 */

void FUN_CODE_aefd(undefined1 *param_1,undefined1 param_2,char param_3,undefined1 param_4,
                  char param_5,char param_6)

{
  undefined1 *puVar1;
  
  if (param_6 != '\0' || param_5 != '\0') {
    if (param_6 != '\0') {
      param_5 = param_5 + '\x01';
    }
    if (param_3 != '\x01') {
      if (param_3 == '\0') {
        do {
          *param_1 = param_4;
          param_1 = param_1 + '\x01';
          param_6 = param_6 + -1;
        } while (param_6 != '\0');
      }
      else if (param_3 == -2) {
        do {
          *(undefined1 *)ZEXT12(param_1) = param_4;
          param_1 = param_1 + '\x01';
          param_6 = param_6 + -1;
        } while (param_6 != '\0');
        return;
      }
      return;
    }
    puVar1 = (undefined1 *)CONCAT11(param_2,param_1);
    do {
      do {
        *puVar1 = param_4;
        puVar1 = puVar1 + 1;
        param_6 = param_6 + -1;
      } while (param_6 != '\0');
      param_5 = param_5 + -1;
    } while (param_5 != '\0');
  }
  return;
}

