/* Address: ram:00068c88; name: FUN_ram_00068c88; body bytes: 100 */

void FUN_ram_00068c88(void)

{
  uint uVar1;
  int iVar2;
  
  gp = 0x20004000;
  thunk_FUN_ram_00065294();
  for (uVar1 = 0; uVar1 < DAT_ram_20001a8d; uVar1 = uVar1 + 1 & 0xff) {
    iVar2 = tmos_isbufset(DAT_ram_20001a88 + uVar1 * 0x10,0xff,6);
    if (iVar2 == 0) {
      thunk_FUN_ram_000652b8(0,DAT_ram_20001a88 + uVar1 * 0x10);
    }
  }
  return;
}

