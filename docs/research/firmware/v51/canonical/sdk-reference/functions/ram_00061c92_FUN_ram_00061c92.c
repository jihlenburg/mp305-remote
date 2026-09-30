/* Address: ram:00061c92; name: FUN_ram_00061c92; body bytes: 180 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00061c92(void)

{
  uint *puVar1;
  uint uVar2;
  
  puVar1 = DAT_ram_20001e88;
  gp = 0x20004000;
  *DAT_ram_20001e88 = *DAT_ram_20001e88 | 0x800000;
  *puVar1 = *puVar1 | 0x10000000;
  puVar1[0xd] = 0x1d0;
  uVar2 = (uint)DAT_ram_20001bd0;
  puVar1[0xb] = uVar2 << 0x19 | 0x80010e78;
  puVar1[0xb] = (uVar2 & 0x3f) << 0x19 | puVar1[0xb] & 0x81ffffff;
  DAT_ram_40001040 = 0xa8;
  if (DAT_ram_20001bd0 < 0xe) {
    DAT_ram_40001022 = DAT_ram_40001022 & 0xffef;
  }
  else {
    DAT_ram_40001022 = DAT_ram_40001022 | 0x10;
  }
  DAT_ram_20001e88[8] = 0x90083;
  DAT_ram_e000e053 = 0x14;
  _DAT_ram_e000e06c = 0x200010a3;
  return;
}

