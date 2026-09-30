/* Address: 00015630; name: cmd_e4; body bytes: 38 */

undefined4 cmd_e4(char *param_1,int param_2,char *param_3,int param_4)

{
  undefined4 uVar1;
  
  *param_3 = *param_1 + '\x01';
  param_3[1] = (char)DAT_1fffa34a + '\x01';
  uVar1 = 2;
  if (param_4 == 6) {
    param_3[2] = param_1[param_2 + -1];
    uVar1 = 3;
  }
  return uVar1;
}

