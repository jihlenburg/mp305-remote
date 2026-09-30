/* Address: ram:000426d6; name: BLE_LibInit; body bytes: 286 */

undefined4 BLE_LibInit(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  if (((*param_1 != 0) && ((*param_1 & 0xffff0000) == 0x20000000)) && ((short)param_1[1] != 0)) {
    iVar1 = tmos_isbufset((int)param_1 + 0x1a,0xff,6);
    uVar2 = 3;
    if ((iVar1 != 1) &&
       ((param_1[2] == 0 || ((uVar2 = 6, param_1[0xd] != 0 && (param_1[0xe] != 0)))))) {
      tmos_memset(&DAT_ram_20001bbc,0,0x3c);
      tmos_memcpy(&DAT_ram_20001bbc,param_1,0x3c);
      if (DAT_ram_20001bc8 == 0) {
        DAT_ram_20001bc8 = 0x100;
      }
      if (DAT_ram_20001bca == '\0') {
        DAT_ram_20001bca = '\x01';
      }
      if (DAT_ram_20001bcc == 0) {
        DAT_ram_20001bcc = 0x1b;
      }
      if (DAT_ram_20001bcb == '\0') {
        DAT_ram_20001bcb = '\x05';
      }
      if (DAT_ram_20001bce == '\0') {
        DAT_ram_20001bce = '\x01';
      }
      if (DAT_ram_20001bcf == '\0') {
        DAT_ram_20001bcf = DAT_ram_20001bcb;
      }
      if (DAT_ram_20001bd0 == '\0') {
        DAT_ram_20001bd0 = '\r';
      }
      if (DAT_ram_20001bd5 == '\0') {
        DAT_ram_20001bd5 = '(';
      }
      if (DAT_ram_20001bd1 == '\0') {
        DAT_ram_20001bd1 = '-';
      }
      if ((char)param_1[6] == '\0') {
        DAT_ram_20001bd4 = 0x3c;
      }
      if (DAT_ram_20001be4 != (code *)0x0) {
        DAT_ram_20001b6c = (*DAT_ram_20001be4)();
      }
      FUN_ram_00042586();
      uVar2 = 0;
    }
    return uVar2;
  }
  return 2;
}

