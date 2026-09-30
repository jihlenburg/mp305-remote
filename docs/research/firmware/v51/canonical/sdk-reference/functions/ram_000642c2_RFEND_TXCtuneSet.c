/* Address: ram:000642c2; name: RFEND_TXCtuneSet; body bytes: 122 */

undefined4 RFEND_TXCtuneSet(char *param_1)

{
  gp = 0x20004000;
  if ((param_1 != (char *)0x0) && (*param_1 == '\x06')) {
    DAT_ram_20001a75 = param_1[1];
    DAT_ram_20001a76 = param_1[2];
    DAT_ram_20001f00 = param_1[3];
    DAT_ram_20001ef0 = param_1[4];
    DAT_ram_20001f01 = param_1[5];
    DAT_ram_20001ef8 = param_1[6];
    if ((param_1[1] == '\0') || (param_1[2] == '\0')) {
      DAT_ram_20001ef4 = 0;
    }
    else {
      DAT_ram_20001ef4 = 0x12345678;
    }
    return 0;
  }
  return 1;
}

