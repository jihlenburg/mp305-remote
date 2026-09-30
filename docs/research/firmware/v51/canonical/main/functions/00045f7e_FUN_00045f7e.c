/* Address: 00045f7e; name: FUN_00045f7e; body bytes: 14 */

undefined4 FUN_00045f7e(int param_1)

{
  if (*(char *)(param_1 + 4) != '\x02') {
    return 0;
  }
  return *(undefined4 *)(param_1 + 0x4c);
}

