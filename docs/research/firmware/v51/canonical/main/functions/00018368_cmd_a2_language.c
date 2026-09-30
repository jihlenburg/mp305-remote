/* Address: 00018368; name: cmd_a2_language; body bytes: 102 */

undefined4 cmd_a2_language(char *param_1,int param_2,char *param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  
  *param_3 = *param_1 + '\x01';
  if (1 < (byte)param_1[1]) {
    param_1[1] = '\0';
  }
  param_3[1] = '\0';
  cVar1 = param_1[1];
  uVar2 = 2;
  if (cVar1 != DAT_1fffa0ce) {
    DAT_1fffa0ce = cVar1;
    if (current_mode == '\x03') {
      FUN_0001d858();
    }
    else {
      FUN_0001aebc(0);
    }
    FUN_0001d958();
    device_state = 1;
  }
  if (param_4 == 6) {
    uVar2 = 3;
    param_3[2] = param_1[param_2 + -1];
  }
  return uVar2;
}

