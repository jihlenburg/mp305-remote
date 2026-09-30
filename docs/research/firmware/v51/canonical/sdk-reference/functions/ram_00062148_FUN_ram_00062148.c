/* Address: ram:00062148; name: FUN_ram_00062148; body bytes: 84 */

void FUN_ram_00062148(uint param_1,int param_2,int param_3,int param_4)

{
  uint *puVar1;
  uint uVar2;
  
  puVar1 = DAT_ram_20001e88;
  gp = 0x20004000;
  if (param_1 != 0) {
    DAT_ram_40001018 = DAT_ram_40001018 | 0x8000;
  }
  DAT_ram_20001e9e = (undefined1)(param_2 << 3);
  DAT_ram_20001e88[0x19] = param_3 << 8 | param_1 | param_2 << 3 | 0x100000;
  puVar1[0x19] = puVar1[0x19] | 4;
  if (param_4 == 0) {
    uVar2 = *puVar1 & 0xdfffffff;
  }
  else {
    uVar2 = *puVar1 | 0x20000000;
  }
  *puVar1 = uVar2;
  return;
}

