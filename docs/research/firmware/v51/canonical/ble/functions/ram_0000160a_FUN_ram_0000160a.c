/* Address: ram:0000160a; name: FUN_ram_0000160a; body bytes: 40 */

void FUN_ram_0000160a(uint param_1)

{
  uint uVar1;
  
  gp = &DAT_ram_20002000;
  for (uVar1 = 0; uVar1 != param_1; uVar1 = uVar1 + 1 & 0xffff) {
    FUN_ram_000015fc(1000);
  }
  return;
}

