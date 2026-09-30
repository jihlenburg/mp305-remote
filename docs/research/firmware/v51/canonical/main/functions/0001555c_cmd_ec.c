/* Address: 0001555c; name: cmd_ec; body bytes: 206 */

undefined4 cmd_ec(char *param_1,int param_2,char *param_3,int param_4)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  
  uVar1 = DAT_1fffaca8;
  uVar3 = DAT_1fffaca8 | DAT_1fffab6a;
  *param_3 = *param_1 + '\x01';
  param_3[1] = DAT_1fffaada;
  param_3[2] = DAT_1fffab06;
  param_3[3] = (char)DAT_1fffab80;
  param_3[4] = (char)((ushort)DAT_1fffab80 >> 8);
  param_3[5] = (char)DAT_1fffaba4;
  param_3[6] = (char)((uint)DAT_1fffaba4 >> 8);
  param_3[7] = (char)((uint)DAT_1fffaba4 >> 0x10);
  param_3[8] = (char)((uint)DAT_1fffaba4 >> 0x18);
  param_3[9] = DAT_1fffab46;
  param_3[10] = DAT_1fffab45;
  param_3[0xb] = (char)DAT_1fffab7e;
  param_3[0xc] = (char)((ushort)DAT_1fffab7e >> 8);
  param_3[0xd] = (char)DAT_1fffaba8;
  param_3[0xe] = (char)((uint)DAT_1fffaba8 >> 8);
  param_3[0xf] = (char)((uint)DAT_1fffaba8 >> 0x10);
  param_3[0x10] = (char)((uint)DAT_1fffaba8 >> 0x18);
  param_3[0x11] = (char)DAT_1fffabac;
  param_3[0x12] = (char)((uint)DAT_1fffabac >> 8);
  param_3[0x13] = (char)((uint)DAT_1fffabac >> 0x10);
  param_3[0x14] = (char)((uint)DAT_1fffabac >> 0x18);
  param_3[0x15] = (char)DAT_1fffab82;
  param_3[0x16] = (char)((ushort)DAT_1fffab82 >> 8);
  param_3[0x17] = DAT_1fffab44;
  param_3[0x18] = DAT_1fffaad1;
  param_3[0x19] = current_mode;
  param_3[0x1a] = DAT_1fffab05;
  param_3[0x1b] = (char)uVar3;
  param_3[0x1c] = (char)(uVar3 >> 8);
  param_3[0x1d] = (char)(uVar1 >> 0x10);
  param_3[0x1e] = (char)(uVar1 >> 0x18);
  uVar2 = 0x1f;
  if (param_4 == 6) {
    uVar2 = 0x20;
    param_3[0x1f] = param_1[param_2 + -1];
  }
  return uVar2;
}

