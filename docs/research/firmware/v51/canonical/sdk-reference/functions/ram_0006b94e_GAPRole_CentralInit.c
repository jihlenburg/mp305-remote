/* Address: ram:0006b94e; name: GAPRole_CentralInit; body bytes: 134 */

void GAPRole_CentralInit(void)

{
  gp = 0x20004000;
  FUN_ram_0005a9b4();
  if (0xfd < (byte)(DAT_ram_200019cc - 1U)) {
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
  }
  FUN_ram_000689a2();
  return;
}

