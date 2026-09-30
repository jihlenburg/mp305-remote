/* Address: ram:0004f568; name: FUN_ram_0004f568; body bytes: 32 */

undefined4 FUN_ram_0004f568(void)

{
  gp = 0x20004000;
  DAT_ram_20001a6c = (undefined4 *)(DAT_ram_20001d50 & 8);
  if ((DAT_ram_20001d50 & 8) != 0) {
    DAT_ram_20001a6c = &DAT_ram_20001d40;
  }
  return 0;
}

