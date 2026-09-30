/* Address: ram:00062a94; name: RF_Config; body bytes: 228 */

undefined4 RF_Config(byte *param_1)

{
  gp = 0x20004000;
  if (*(int *)(param_1 + 0x10) == 0) {
    return 1;
  }
  if (((*param_1 & 0x40) != 0) && (*(int *)(param_1 + 4) == 0)) {
    gp = 0x20004000;
    return 2;
  }
  tmos_memset(&DAT_ram_20001eb4,0,0x20);
  tmos_memcpy(&DAT_ram_20001eb4,param_1,0x20);
  if (DAT_ram_20001ecd == '\0') {
    DAT_ram_20001ecd = '(';
  }
  if (DAT_ram_20001ece == '\0') {
    DAT_ram_20001ece = '\b';
  }
  if (DAT_ram_20001ecf == '\0') {
    DAT_ram_20001ecf = '\x11';
  }
  if (DAT_ram_20001ed0 == '\0') {
    DAT_ram_20001ed0 = -5;
  }
  if (DAT_ram_20001ed1 == 0) {
    DAT_ram_20001ed1 = 0xfb;
  }
  if (DAT_ram_20001ed8 != 0) {
    FUN_ram_20000104();
  }
  DAT_ram_20001ed8 = 0;
  if ((DAT_ram_20001eb4 & 1) != 0) {
    DAT_ram_20001ed8 = FUN_ram_20000040(DAT_ram_20001ed1 + 2,0x49);
  }
  DAT_ram_20001ee8 = DAT_ram_20001ebc;
  DAT_ram_20001ee3 = DAT_ram_20001eb5;
  return 0;
}

