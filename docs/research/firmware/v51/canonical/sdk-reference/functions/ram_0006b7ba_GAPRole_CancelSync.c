/* Address: ram:0006b7ba; name: GAPRole_CancelSync; body bytes: 4 */

undefined4 GAPRole_CancelSync(void)

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

