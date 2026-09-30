/* Address: ram:0004bece; name: FUN_ram_0004bece; body bytes: 62 */

void FUN_ram_0004bece(undefined1 param_1)

{
  gp = 0x20004000;
  FUN_ram_000481c8();
  FUN_ram_00049e46();
  DAT_ram_200019b4 = param_1;
  FUN_ram_00049e22(DAT_ram_20001a40);
  DAT_ram_200019c2 = param_1;
  linkDB_Register(FUN_ram_0004bd42);
  return;
}

