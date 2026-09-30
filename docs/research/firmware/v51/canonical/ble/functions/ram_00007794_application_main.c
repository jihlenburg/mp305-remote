/* Address: ram:00007794; name: application_main; body bytes: 108 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void application_main(void)

{
  gp = &DAT_ram_20002000;
  FUN_ram_200023fe(0x48);
  FUN_ram_00002498(0xffffefff,2);
  FUN_ram_0000253e(0xffffbfef,2);
  DAT_ram_400010c8 = DAT_ram_400010c8 | 0x80;
  FUN_ram_0000253e(0x80,3);
  FUN_ram_00002812();
  FUN_ram_000032b6();
  FUN_ram_000033d0();
  (*_DAT_ram_000401a0)();
  (*_DAT_ram_000401ac)();
  initialize_ble_application();
  FUN_ram_00005744();
  FUN_ram_2000280a();
  return;
}

