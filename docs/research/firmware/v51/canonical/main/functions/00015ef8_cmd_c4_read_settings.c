/* Address: 00015ef8; name: cmd_c4_read_settings; body bytes: 94 */

undefined4 cmd_c4_read_settings(char *param_1,int param_2,char *param_3,int param_4)

{
  undefined4 uVar1;
  
  *param_3 = *param_1 + '\x01';
  param_3[1] = DAT_1fffaaf9;
  param_3[2] = DAT_1fffaafe;
  param_3[3] = DAT_1fffaafa;
  param_3[4] = DAT_1fffaaff;
  param_3[5] = DAT_1fffaafb;
  param_3[6] = (char)DAT_1fffab62;
  param_3[7] = (char)((ushort)DAT_1fffab62 >> 8);
  param_3[8] = (char)DAT_1fffab64;
  param_3[9] = (char)((ushort)DAT_1fffab64 >> 8);
  param_3[10] = (char)DAT_1fffab70;
  param_3[0xb] = (char)((ushort)DAT_1fffab70 >> 8);
  uVar1 = 0xc;
  if (param_4 == 6) {
    uVar1 = 0xd;
    param_3[0xc] = param_1[param_2 + -1];
  }
  return uVar1;
}

