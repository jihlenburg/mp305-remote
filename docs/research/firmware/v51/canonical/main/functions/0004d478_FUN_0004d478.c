/* Address: 0004d478; name: FUN_0004d478; body bytes: 32 */

bool FUN_0004d478(int *param_1)

{
  do {
    param_1 = (int *)*param_1;
    if (param_1 == (int *)0x0) {
      return false;
    }
  } while ((*(byte *)(param_1 + 8) & 0xc) == 0);
  return (*(byte *)(param_1 + 8) & 0xf) >> 2 == 1;
}

