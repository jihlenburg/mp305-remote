/* Address: ram:0005ac84; name: FUN_ram_0005ac84; body bytes: 34 */

undefined4 FUN_ram_0005ac84(int param_1)

{
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x15) = 1;
  if (*(int *)(param_1 + 0x110) != 0) {
    *(undefined1 *)(*(int *)(param_1 + 0x110) + 2) = 0xb;
    *(undefined1 *)(param_1 + 0x10) = 0x37;
    return 0;
  }
  return 1;
}

