/* Address: 0001565c; name: cmd_dc; body bytes: 52 */

undefined4 cmd_dc(char *param_1,int param_2,char *param_3,int param_4)

{
  undefined4 uVar1;
  
  *param_3 = *param_1 + '\x01';
  param_3[1] = (&DAT_1fffa3fe)[DAT_1fffa408];
  param_3[2] = (&DAT_1fffa3f4)[DAT_1fffa408];
  uVar1 = 3;
  if (param_4 == 6) {
    param_3[3] = param_1[param_2 + -1];
    uVar1 = 4;
  }
  return uVar1;
}

