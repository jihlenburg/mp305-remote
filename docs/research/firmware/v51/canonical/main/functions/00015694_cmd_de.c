/* Address: 00015694; name: cmd_de; body bytes: 540 */

undefined4 cmd_de(char *param_1,int param_2,char *param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  
  *param_3 = *param_1 + '\x01';
  param_3[1] = DAT_1fffaace;
  param_3[2] = DAT_1fffaada;
  param_3[3] = DAT_1fffab06;
  param_3[4] = (char)DAT_1fffab78;
  param_3[5] = (char)((ushort)DAT_1fffab78 >> 8);
  param_3[6] = (char)DAT_1fffab7a;
  param_3[7] = (char)((ushort)DAT_1fffab7a >> 8);
  cVar1 = '\0';
  if (current_mode == '\x01') {
    param_3[8] = (char)DAT_1fffab94;
    param_3[9] = (char)((ushort)(undefined2)DAT_1fffab94 >> 8);
    param_3[10] = '\0';
    param_3[0xb] = '\0';
  }
  else {
    param_3[8] = (char)DAT_1fffab9c;
    param_3[9] = (char)((uint)DAT_1fffab9c >> 8);
    param_3[10] = (char)((uint)DAT_1fffab9c >> 0x10);
    param_3[0xb] = (char)((uint)DAT_1fffab9c >> 0x18);
  }
  param_3[0xc] = (char)DAT_1fffaba0;
  param_3[0xd] = (char)((uint)DAT_1fffaba0 >> 8);
  param_3[0xe] = (char)((uint)DAT_1fffaba0 >> 0x10);
  param_3[0xf] = (char)((uint)DAT_1fffaba0 >> 0x18);
  param_3[0x10] = (char)DAT_1fffab7c;
  param_3[0x11] = (char)((ushort)DAT_1fffab7c >> 8);
  if (DAT_1fffab48 < 0) {
    param_3[0x12] = '\x01';
  }
  else {
    param_3[0x12] = (char)DAT_1fffab48 + '\x01';
  }
  param_3[0x13] = DAT_1fffaad1;
  param_3[0x14] = current_mode;
  param_3[0x15] = DAT_1fffab05;
  param_3[0x16] = DAT_1fffaaec;
  if (DAT_1fffab84 < 0) {
    param_3[0x17] = '\0';
    param_3[0x18] = '\0';
    param_3[0x19] = '\0';
  }
  else {
    param_3[0x17] = (char)DAT_1fffab84;
    param_3[0x18] = (char)((uint)DAT_1fffab84 >> 8);
    param_3[0x19] = (char)((uint)DAT_1fffab84 >> 0x10);
    cVar1 = (char)((uint)DAT_1fffab84 >> 0x18);
  }
  param_3[0x1a] = cVar1;
  param_3[0x1b] = DAT_1fffaaeb;
  param_3[0x1c] = DAT_1fffacac;
  param_3[0x1d] = (char)DAT_1fffacae;
  param_3[0x1e] = (char)DAT_1fffacb0;
  param_3[0x1f] = (char)((ushort)DAT_1fffacb0 >> 8);
  param_3[0x20] = (char)DAT_1fffacb4;
  param_3[0x21] = (char)DAT_1fffacb2;
  param_3[0x22] = (char)DAT_1fffacb6;
  param_3[0x23] = (char)DAT_1fffacb8;
  param_3[0x24] = (char)DAT_1fffacbc;
  param_3[0x25] = (char)DAT_1fffacba;
  param_3[0x26] = DAT_1fff9b8e;
  param_3[0x27] = (char)DAT_1fff9b3c;
  param_3[0x28] = (char)((uint)DAT_1fff9b3c >> 8);
  param_3[0x29] = (char)((uint)DAT_1fff9b3c >> 0x10);
  param_3[0x2a] = (char)((uint)DAT_1fff9b3c >> 0x18);
  param_3[0x2b] = (char)DAT_1fff9b40;
  param_3[0x2c] = (char)((uint)DAT_1fff9b40 >> 8);
  param_3[0x2d] = (char)((uint)DAT_1fff9b40 >> 0x10);
  param_3[0x2e] = (char)((uint)DAT_1fff9b40 >> 0x18);
  param_3[0x2f] = (char)DAT_1fff9b44;
  param_3[0x30] = (char)((uint)DAT_1fff9b44 >> 8);
  param_3[0x31] = (char)((uint)DAT_1fff9b44 >> 0x10);
  param_3[0x32] = (char)((uint)DAT_1fff9b44 >> 0x18);
  param_3[0x33] = (char)DAT_1fff9b48;
  param_3[0x34] = (char)((uint)DAT_1fff9b48 >> 8);
  param_3[0x35] = (char)((uint)DAT_1fff9b48 >> 0x10);
  param_3[0x36] = (char)((uint)DAT_1fff9b48 >> 0x18);
  param_3[0x37] = (char)DAT_1fff9b4c;
  param_3[0x38] = (char)((uint)DAT_1fff9b4c >> 8);
  param_3[0x39] = (char)((uint)DAT_1fff9b4c >> 0x10);
  param_3[0x3a] = (char)((uint)DAT_1fff9b4c >> 0x18);
  param_3[0x3b] = (char)DAT_1fff9b50;
  param_3[0x3c] = (char)((uint)DAT_1fff9b50 >> 8);
  param_3[0x3d] = (char)((uint)DAT_1fff9b50 >> 0x10);
  param_3[0x3e] = (char)((uint)DAT_1fff9b50 >> 0x18);
  param_3[0x3f] = (char)DAT_1fffab6a;
  param_3[0x40] = (char)((ushort)DAT_1fffab6a >> 8);
  param_3[0x41] = (char)DAT_1fffa980;
  param_3[0x42] = (char)((uint)DAT_1fffa980 >> 8);
  param_3[0x43] = (char)((uint)DAT_1fffa980 >> 0x10);
  param_3[0x44] = (char)((uint)DAT_1fffa980 >> 0x18);
  uVar2 = 0x45;
  if (param_4 == 6) {
    uVar2 = 0x46;
    param_3[0x45] = param_1[param_2 + -1];
  }
  return uVar2;
}

