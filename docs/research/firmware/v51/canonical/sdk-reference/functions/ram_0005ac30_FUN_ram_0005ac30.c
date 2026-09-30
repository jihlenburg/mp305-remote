/* Address: ram:0005ac30; name: FUN_ram_0005ac30; body bytes: 38 */

undefined4 FUN_ram_0005ac30(int param_1)

{
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x15) = 2;
  if (*(int *)(param_1 + 0x110) != 0) {
    *(undefined1 *)(*(int *)(param_1 + 0x110) + 2) = 7;
    *(undefined1 *)(*(int *)(param_1 + 0x110) + 3) = *(undefined1 *)(param_1 + 0x2c);
    return 0;
  }
  return 1;
}

