/* Address: ram:00063f76; name: RF_RoleInit; body bytes: 80 */

undefined4 RF_RoleInit(void)

{
  gp = 0x20004000;
  FUN_ram_000626ac();
  tmos_memset(&DAT_ram_20001ed4,0,0x1c);
  DAT_ram_20001ed4 = 0xffffffff;
  DAT_ram_20001ee4 = TMOS_ProcessEventRegister(FUN_ram_0006372c);
  FUN_ram_00042570(FUN_ram_00062ff6,5);
  return 0;
}

