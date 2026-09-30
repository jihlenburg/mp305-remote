/* Address: 00050b0e; name: FUN_00050b0e; body bytes: 12 */

undefined4 FUN_00050b0e(int param_1)

{
  if (*(char *)(param_1 + 8) != '\0') {
    return 0;
  }
  return 1;
}

