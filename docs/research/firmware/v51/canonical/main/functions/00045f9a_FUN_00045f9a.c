/* Address: 00045f9a; name: FUN_00045f9a; body bytes: 14 */

undefined4 FUN_00045f9a(int param_1)

{
  if (*(char *)(param_1 + 4) != '\x04') {
    return 0;
  }
  return *(undefined4 *)(param_1 + 0x4c);
}

