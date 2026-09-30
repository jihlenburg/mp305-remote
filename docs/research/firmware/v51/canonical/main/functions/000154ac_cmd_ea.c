/* Address: 000154ac; name: cmd_ea; body bytes: 172 */

undefined4 cmd_ea(char *param_1,int param_2,char *param_3,int param_4)

{
  undefined4 uVar1;
  
  *param_3 = *param_1 + '\x01';
  param_3[1] = DAT_1fffac94._2_1_;
  param_3[2] = (char)DAT_1fffac94;
  param_3[3] = (char)((ushort)(undefined2)DAT_1fffac94 >> 8);
  param_3[4] = (char)DAT_1fffac90;
  param_3[5] = DAT_1fffac90._2_1_;
  param_3[6] = (char)((ushort)DAT_1fffac90._2_2_ >> 8);
  param_3[7] = DAT_1fffac98;
  param_3[8] = DAT_1fffac99;
  param_3[9] = (char)DAT_1fffac9c;
  param_3[10] = (char)((uint)DAT_1fffac9c >> 8);
  param_3[0xb] = (char)((uint)DAT_1fffac9c >> 0x10);
  param_3[0xc] = (char)((uint)DAT_1fffac9c >> 0x18);
  param_3[0xd] = (char)DAT_1fffaca0;
  param_3[0xe] = (char)((uint)DAT_1fffaca0 >> 8);
  param_3[0xf] = (char)((uint)DAT_1fffaca0 >> 0x10);
  param_3[0x10] = (char)((uint)DAT_1fffaca0 >> 0x18);
  param_3[0x11] = (char)DAT_1fffaca4;
  param_3[0x12] = (char)((uint)DAT_1fffaca4 >> 8);
  param_3[0x13] = (char)((uint)DAT_1fffaca4 >> 0x10);
  param_3[0x14] = (char)((uint)DAT_1fffaca4 >> 0x18);
  uVar1 = 0x15;
  if (param_4 == 6) {
    uVar1 = 0x16;
    param_3[0x15] = param_1[param_2 + -1];
  }
  return uVar1;
}

