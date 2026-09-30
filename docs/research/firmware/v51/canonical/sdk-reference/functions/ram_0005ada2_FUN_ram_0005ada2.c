/* Address: ram:0005ada2; name: FUN_ram_0005ada2; body bytes: 26 */

undefined4 FUN_ram_0005ada2(int param_1)

{
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x15) = 1;
  if (*(int *)(param_1 + 0x110) != 0) {
    *(undefined1 *)(*(int *)(param_1 + 0x110) + 2) = 0x13;
    return 0;
  }
  return 1;
}

