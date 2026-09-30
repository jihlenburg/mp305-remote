/* Address: ram:00004f90; name: FUN_ram_00004f90; body bytes: 42 */

void FUN_ram_00004f90(uint param_1)

{
  uint uVar1;
  
  gp = &DAT_ram_20002000;
  for (uVar1 = 0; (uVar1 & 0xff) < param_1; uVar1 = uVar1 + 1) {
    *(byte *)(DAT_ram_20002f50 + uVar1 + 0x80) = ~*(byte *)(DAT_ram_20002f50 + uVar1 + 0x40);
  }
  FUN_ram_00002aa0();
  return;
}

