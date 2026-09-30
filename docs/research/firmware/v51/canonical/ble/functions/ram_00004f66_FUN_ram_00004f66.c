/* Address: ram:00004f66; name: FUN_ram_00004f66; body bytes: 42 */

void FUN_ram_00004f66(uint param_1)

{
  uint uVar1;
  
  gp = &DAT_ram_20002000;
  for (uVar1 = 0; (uVar1 & 0xff) < param_1; uVar1 = uVar1 + 1) {
    ((byte *)(DAT_ram_20002f5c + uVar1))[0x40] = ~*(byte *)(DAT_ram_20002f5c + uVar1);
  }
  FUN_ram_00002a8a();
  return;
}

