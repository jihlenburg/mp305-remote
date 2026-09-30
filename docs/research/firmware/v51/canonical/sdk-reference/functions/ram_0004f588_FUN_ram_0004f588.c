/* Address: ram:0004f588; name: FUN_ram_0004f588; body bytes: 32 */

undefined4 FUN_ram_0004f588(void)

{
  gp = 0x20004000;
  DAT_ram_20001a70 = (undefined4 *)(DAT_ram_20001d50 & 4);
  if ((DAT_ram_20001d50 & 4) != 0) {
    DAT_ram_20001a70 = &DAT_ram_20001d34;
  }
  return 0;
}

