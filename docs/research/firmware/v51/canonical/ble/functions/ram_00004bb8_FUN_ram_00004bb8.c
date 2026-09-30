/* Address: ram:00004bb8; name: FUN_ram_00004bb8; body bytes: 40 */

void FUN_ram_00004bb8(void)

{
  int iVar1;
  
  gp = &DAT_ram_20002000;
  iVar1 = FUN_ram_00003798();
  if (iVar1 != 0) {
    FUN_ram_00004b9c();
  }
  iVar1 = FUN_ram_000037b0();
  if (iVar1 != 0) {
    FUN_ram_00004964();
  }
  iVar1 = FUN_ram_000037c8();
  if (iVar1 != 0) {
    FUN_ram_00004bb2();
  }
  FUN_ram_000037e0();
  FUN_ram_000037f8();
  return;
}

