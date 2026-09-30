/* Address: ram:0005e0de; name: FUN_ram_0005e0de; body bytes: 200 */

void FUN_ram_0005e0de(int param_1)

{
  uint *puVar1;
  
  gp = 0x20004000;
  FUN_ram_0005dfb2();
  DAT_ram_20001e88[0xb] = DAT_ram_20001e88[0xb] & 0x81ffffff | (DAT_ram_20001bd0 & 0x3f) << 0x19;
  DAT_ram_40001040 = 0xa8;
  if (DAT_ram_20001bd0 < 0xe) {
    DAT_ram_40001022 = DAT_ram_40001022 & 0xffef;
  }
  else {
    DAT_ram_40001022 = DAT_ram_40001022 | 0x10;
  }
  *(undefined4 *)(DAT_ram_20001eb0 + 0x70) = *(undefined4 *)(param_1 + 0x74);
  puVar1 = DAT_ram_20001e88;
  *DAT_ram_20001e88 = *DAT_ram_20001e88 | 0x800000;
  puVar1[0xb] = puVar1[0xb] & 0xfffffffc;
  FUN_ram_0005dd6c(param_1);
  FUN_ram_200010ec();
  if ((DAT_ram_20001e95 & 1) == 0) {
    DAT_ram_20001e98 = 0;
    *(undefined1 *)(param_1 + 10) = 0xa0;
  }
  else {
    DAT_ram_20001e95 = 0;
  }
  return;
}

