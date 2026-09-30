/* Address: 00045f8c; name: FUN_00045f8c; body bytes: 14 */

undefined4 FUN_00045f8c(int param_1)

{
  if (*(char *)(param_1 + 4) != '\x01') {
    return 0;
  }
  return *(undefined4 *)(param_1 + 0x4c);
}

