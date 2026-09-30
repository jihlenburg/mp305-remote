/* Address: ram:000525ec; name: thunk_FUN_ram_00067e9a; body bytes: 4 */

undefined4 thunk_FUN_ram_00067e9a(void)

{
  gp = 0x20004000;
  if (DAT_ram_20001dd8 != 0) {
    if ((-1 < (int)(*(uint *)(DAT_ram_20001dd8 + 0x1c) << 0x11)) &&
       ((*(uint *)(DAT_ram_20001dd8 + 0x1c) & 2) != 0)) {
      FUN_ram_0005f570(0xc);
      return 0;
    }
  }
  return 0xc;
}

