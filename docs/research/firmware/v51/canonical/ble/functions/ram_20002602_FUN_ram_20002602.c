/* Address: ram:20002602; name: FUN_ram_20002602; body bytes: 40 */

void FUN_ram_20002602(uint param_1)

{
  uint uVar1;
  
  gp = &DAT_ram_20002000;
  for (uVar1 = 0; uVar1 != param_1; uVar1 = uVar1 + 1 & 0xffff) {
    FUN_ram_200025f4(1000);
  }
  return;
}

