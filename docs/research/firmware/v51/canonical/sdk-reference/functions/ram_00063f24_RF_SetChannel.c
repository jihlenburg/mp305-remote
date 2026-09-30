/* Address: ram:00063f24; name: RF_SetChannel; body bytes: 82 */

void RF_SetChannel(uint param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  gp = 0x20004000;
  if (DAT_ram_20001ee0 == '\0') {
    if ((*(uint *)(DAT_ram_20001efc + 0x2c) >> 1 & 1) == 0) {
      uVar2 = param_1 & 0xff;
      DAT_ram_20001eb5 = (undefined1)param_1;
      uVar1 = 0;
      DAT_ram_20001ee3 = DAT_ram_20001eb5;
    }
    else {
      uVar1 = 2;
      uVar2 = param_1;
      DAT_ram_20001eb8 = param_1;
      if (DAT_ram_20001e9b != '\x03') {
        uVar1 = 1;
      }
    }
    FUN_ram_00062784(uVar2,uVar1);
    return;
  }
  return;
}

