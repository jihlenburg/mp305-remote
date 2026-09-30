/* Address: ram:0004a3aa; name: FUN_ram_0004a3aa; body bytes: 28 */

void FUN_ram_0004a3aa(int param_1)

{
  gp = 0x20004000;
  FUN_ram_00048886(param_1 + 2);
  *(undefined1 *)(param_1 + 3) = 0xff;
  return;
}

