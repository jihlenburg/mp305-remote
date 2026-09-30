/* Address: ram:0006049c; name: FUN_ram_0006049c; body bytes: 30 */

void FUN_ram_0006049c(int param_1)

{
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x31) = 0xff;
  FUN_ram_0005d5f6(0,0x80,0x11);
  FUN_ram_000603de();
  return;
}

