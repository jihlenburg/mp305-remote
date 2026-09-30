/* Address: ram:0006b8de; name: GAPRole_PeripheralInit; body bytes: 112 */

void GAPRole_PeripheralInit(void)

{
  gp = 0x20004000;
  FUN_ram_0006179c();
  TMOS_ProcessEventRegister(FUN_ram_0004c9e0);
  FUN_ram_0004c892();
  TMOS_ProcessEventRegister(FUN_ram_00045266);
  FUN_ram_0004521e();
  TMOS_ProcessEventRegister(&LAB_ram_0004920a);
  FUN_ram_000491d8();
  TMOS_ProcessEventRegister(FUN_ram_0004f44a);
  FUN_ram_0004f5a8();
  TMOS_ProcessEventRegister(FUN_ram_0006a822);
  FUN_ram_00069e18();
  TMOS_ProcessEventRegister(&LAB_ram_0004bf0c);
  FUN_ram_0004bece();
  FUN_ram_0006b1a8();
  return;
}

