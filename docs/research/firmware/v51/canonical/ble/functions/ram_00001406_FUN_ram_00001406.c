/* Address: ram:00001406; name: FUN_ram_00001406; body bytes: 372 */

void FUN_ram_00001406(uint param_1)

{
  int iVar1;
  
  gp = &DAT_ram_20002000;
  if ((param_1 & 0x20) == 0) {
    if ((param_1 & 0x40) == 0) {
      DAT_ram_40001008 = DAT_ram_40001008 | 0xc0;
    }
    else {
      if ((DAT_ram_4000100a & 0x10) == 0) {
        DAT_ram_4000100a = DAT_ram_4000100a | 0x10;
        iVar1 = 2000;
        do {
          iVar1 = iVar1 + -1;
        } while (iVar1 != 0);
      }
      DAT_ram_40001008 = (ushort)param_1 & 0x1f | 0x40;
      if (param_1 == 0x46) {
        DAT_ram_40001807 = 2;
      }
      else {
        DAT_ram_40001807 = 0x52;
      }
    }
  }
  else {
    if ((DAT_ram_4000100a & 4) == 0) {
      DAT_ram_4000100a = DAT_ram_4000100a | 4;
      iVar1 = 0x4b0;
      do {
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    DAT_ram_40001008 = (ushort)param_1 & 0x1f;
    DAT_ram_40001807 = 0x51;
  }
  DAT_ram_4000104b = DAT_ram_4000104b & 0xdf | 0x80;
  DAT_ram_40001040 = 0;
  return;
}

