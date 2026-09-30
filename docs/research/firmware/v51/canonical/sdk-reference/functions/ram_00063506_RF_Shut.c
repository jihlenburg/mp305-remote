/* Address: ram:00063506; name: RF_Shut; body bytes: 128 */

undefined4 RF_Shut(void)

{
  gp = 0x20004000;
  DAT_ram_20001ee2 = 0;
  if (DAT_ram_20001ed8 != 0) {
    FUN_ram_20000104();
  }
  DAT_ram_20001ed8 = 0;
  if ((DAT_ram_20001e9d != '\0') && (DAT_ram_20001e9c == '\b')) {
    DAT_ram_20001e9d = '\0';
  }
  if ((byte)(DAT_ram_20001e9b - 6U) < 2) {
    DAT_ram_20001e9c = DAT_ram_20001e9b;
    DAT_ram_20001e9d = '\x01';
  }
  FUN_ram_00062262();
  tmos_stop_task(DAT_ram_20001ee4,0x10);
  FUN_ram_00042570(0,0);
  return 0;
}

