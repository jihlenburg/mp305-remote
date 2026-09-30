/* Address: CODE:6c92; name: FUN_CODE_6c92; body bytes: 119 */

void FUN_CODE_6c92(char *param_1,undefined1 param_2,char param_3,undefined1 param_4,
                  undefined1 param_5,char param_6)

{
  undefined1 *puVar1;
  
  _1_4 = 0;
  FUN_CODE_621e();
  if (*param_1 == param_6) {
    return;
  }
  if (param_6 == '\x01') {
LAB_CODE_6cb0:
    FUN_CODE_6276();
    FUN_CODE_6248();
    *param_1 = '\0';
    param_1[1] = '\0';
    puVar1 = (undefined1 *)(CONCAT11(param_2,param_3) + 3);
    *puVar1 = 0;
    FUN_CODE_624e(param_3 + '\x04');
    *puVar1 = 0;
  }
  else {
    if (param_6 == '\x02') {
      param_1 = (char *)(CONCAT11(param_4,param_5) + 1);
      *param_1 = '\x01';
      FUN_CODE_2ed4();
      if (param_6 != '\x03') {
        if (param_6 == '\x05') goto LAB_CODE_6cf6;
        if (param_6 != '\x06') goto LAB_CODE_6d00;
        goto LAB_CODE_6cb0;
      }
    }
    else if (param_6 != '\x03') {
      if (param_6 == '\x05') {
LAB_CODE_6cf6:
        _1_4 = 1;
      }
      else if ((param_6 != '\x06') && (param_6 != '\0')) goto LAB_CODE_6d00;
      goto LAB_CODE_6cb0;
    }
    FUN_CODE_621e();
    param_1 = param_1 + 1;
    FUN_CODE_6263();
    FUN_CODE_8265(param_1[1]);
  }
LAB_CODE_6d00:
  FUN_CODE_6293(0x752);
  return;
}

