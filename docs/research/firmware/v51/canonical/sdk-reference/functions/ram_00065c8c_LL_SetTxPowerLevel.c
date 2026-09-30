/* Address: ram:00065c8c; name: LL_SetTxPowerLevel; body bytes: 160 */

undefined4 LL_SetTxPowerLevel(uint param_1)

{
  undefined4 uVar1;
  
  gp = 0x20004000;
  if (param_1 < 0x40) {
    DAT_ram_20001bd0 = (byte)param_1;
    *(uint *)(DAT_ram_20001e88 + 0x2c) =
         (param_1 & 0x3f) << 0x19 | *(uint *)(DAT_ram_20001e88 + 0x2c) & 0x81ffffff;
    DAT_ram_40001040 = 0xa8;
    if (DAT_ram_20001bd0 < 0xe) {
      DAT_ram_40001022 = DAT_ram_40001022 & 0xffef;
    }
    else {
      DAT_ram_40001022 = DAT_ram_40001022 | 0x10;
    }
    uVar1 = 0;
    if ((*(uint *)(DAT_ram_20001efc + 0x54) >> 8 & 2) != 0) {
      *(uint *)(DAT_ram_20001efc + 0x10) =
           *(uint *)(DAT_ram_20001efc + 0x10) & 0xffffc0ff | (DAT_ram_20001bd0 & 0x3f) << 8;
      return uVar1;
    }
  }
  else {
    uVar1 = 0x12;
  }
  return uVar1;
}

