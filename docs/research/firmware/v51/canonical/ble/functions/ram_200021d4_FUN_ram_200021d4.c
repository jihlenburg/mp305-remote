/* Address: ram:200021d4; name: FUN_ram_200021d4; body bytes: 304 */

void FUN_ram_200021d4(ushort param_1)

{
  int local_20;
  undefined2 uStack_1c;
  int iStack_18;
  undefined2 uStack_14;
  
  gp = &DAT_ram_20002000;
  local_20 = 0;
  uStack_1c = 0;
  FUN_ram_200028d6(6,0x7f018,&local_20,0);
  DAT_ram_4000104e = DAT_ram_4000104e | 3;
  if (0x3fff < DAT_ram_40001038) {
    DAT_ram_4000102e = DAT_ram_4000102e & 0xfc | 1;
  }
  DAT_ram_40001024 = 0;
  DAT_ram_e000ed10 = DAT_ram_e000ed10 | 4;
  DAT_ram_40001020 = DAT_ram_40001020 & 0x600 | param_1 | 0x9004;
  DAT_ram_40001040 = 0xa8;
  DAT_ram_4000100f = DAT_ram_4000100f | 0x40;
  DAT_ram_4000104b = DAT_ram_4000104b | 0x20;
  do {
    DAT_ram_e000ed10 = DAT_ram_e000ed10 & 0xfffffff7;
    wfi();
    FUN_ram_200025f4(0x46);
    iStack_18 = 0;
    uStack_14 = 0;
    FUN_ram_200028d6(6,0x7f018,&iStack_18,0);
  } while (iStack_18 != local_20);
  DAT_ram_4000104b = DAT_ram_4000104b & 0xdf;
  DAT_ram_40001040 = 0;
  return;
}

