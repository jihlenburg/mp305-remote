/* Address: ram:0005ad74; name: FUN_ram_0005ad74; body bytes: 46 */

undefined4 FUN_ram_0005ad74(int param_1)

{
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x15) = 1;
  if (*(int *)(param_1 + 0x110) != 0) {
    *(undefined1 *)(*(int *)(param_1 + 0x110) + 2) = 0x12;
    *(undefined1 *)(param_1 + 0x10) = 0x4a;
    *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 4;
    return 0;
  }
  return 1;
}

