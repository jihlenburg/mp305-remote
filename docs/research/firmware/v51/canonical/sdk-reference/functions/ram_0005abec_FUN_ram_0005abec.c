/* Address: ram:0005abec; name: FUN_ram_0005abec; body bytes: 34 */

undefined4 FUN_ram_0005abec(int param_1)

{
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x15) = 1;
  if (*(int *)(param_1 + 0x110) != 0) {
    *(undefined1 *)(*(int *)(param_1 + 0x110) + 2) = 5;
    *(undefined1 *)(param_1 + 0x10) = 0x2b;
    return 0;
  }
  return 1;
}

