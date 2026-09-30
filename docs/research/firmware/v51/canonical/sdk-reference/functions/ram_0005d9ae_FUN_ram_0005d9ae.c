/* Address: ram:0005d9ae; name: FUN_ram_0005d9ae; body bytes: 62 */

void FUN_ram_0005d9ae(int param_1)

{
  gp = 0x20004000;
  if (*(char *)(param_1 + 0x7d) != -1) {
    FUN_ram_00042494();
    *(undefined1 *)(param_1 + 0x7d) = 0xff;
  }
  *(undefined1 *)(param_1 + 0x81) = 0xff;
  FUN_ram_0005d5f6(0,0x80,0x10);
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) & 0xfffffff1;
  return;
}

