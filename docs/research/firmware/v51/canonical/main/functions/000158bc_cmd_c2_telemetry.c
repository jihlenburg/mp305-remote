/* Address: 000158bc; name: cmd_c2_telemetry; body bytes: 258 */

undefined4 cmd_c2_telemetry(char *param_1,int param_2,char *param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  
  *param_3 = *param_1 + '\x01';
  param_3[1] = DAT_1fffaace;
  param_3[2] = DAT_1fffaada;
  param_3[3] = DAT_1fffab06;
  param_3[4] = (char)DAT_1fffab78;
  param_3[5] = (char)((ushort)DAT_1fffab78 >> 8);
  param_3[6] = (char)DAT_1fffab74;
  param_3[7] = (char)((ushort)DAT_1fffab74 >> 8);
  param_3[8] = (char)DAT_1fffab7a;
  param_3[9] = (char)((ushort)DAT_1fffab7a >> 8);
  param_3[10] = (char)DAT_1fffab76;
  param_3[0xb] = (char)((ushort)DAT_1fffab76 >> 8);
  param_3[0xc] = (char)DAT_1fffab9c;
  param_3[0xd] = (char)((uint)DAT_1fffab9c >> 8);
  param_3[0xe] = (char)((uint)DAT_1fffab9c >> 0x10);
  param_3[0xf] = (char)((uint)DAT_1fffab9c >> 0x18);
  param_3[0x10] = (char)DAT_1fffaba0;
  param_3[0x11] = (char)((uint)DAT_1fffaba0 >> 8);
  param_3[0x12] = (char)((uint)DAT_1fffaba0 >> 0x10);
  param_3[0x13] = (char)((uint)DAT_1fffaba0 >> 0x18);
  param_3[0x14] = (char)DAT_1fffab7c;
  param_3[0x15] = (char)((ushort)DAT_1fffab7c >> 8);
  param_3[0x16] = DAT_1fffaade;
  param_3[0x17] = DAT_1fffaae4;
  param_3[0x18] = DAT_1fffaadc;
  param_3[0x19] = DAT_1fffaad1;
  param_3[0x1a] = current_mode;
  param_3[0x1b] = DAT_1fffab03;
  param_3[0x1c] = DAT_1fffab04;
  param_3[0x1d] = DAT_1fffab05;
  param_3[0x1e] = (char)DAT_1fffab6a;
  param_3[0x1f] = (char)((ushort)DAT_1fffab6a >> 8);
  cVar1 = DAT_1fffaadd;
  if (DAT_1ffe02a0 == 0) {
    cVar1 = '\x01';
  }
  param_3[0x20] = cVar1;
  param_3[0x21] = (char)DAT_1fffa980;
  param_3[0x22] = (char)((uint)DAT_1fffa980 >> 8);
  param_3[0x23] = (char)((uint)DAT_1fffa980 >> 0x10);
  param_3[0x24] = (char)((uint)DAT_1fffa980 >> 0x18);
  uVar2 = 0x25;
  if (param_4 == 6) {
    uVar2 = 0x26;
    param_3[0x25] = param_1[param_2 + -1];
  }
  return uVar2;
}

