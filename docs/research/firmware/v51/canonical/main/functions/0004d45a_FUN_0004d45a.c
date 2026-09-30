/* Address: 0004d45a; name: FUN_0004d45a; body bytes: 30 */

bool FUN_0004d45a(int *param_1)

{
  do {
    param_1 = (int *)*param_1;
    if (param_1 == (int *)0x0) {
      return false;
    }
  } while ((*(byte *)(param_1 + 8) & 3) == 0);
  return (*(byte *)(param_1 + 8) & 3) == 1;
}

