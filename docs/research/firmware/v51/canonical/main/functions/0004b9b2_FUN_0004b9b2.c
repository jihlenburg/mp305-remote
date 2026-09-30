/* Address: 0004b9b2; name: FUN_0004b9b2; body bytes: 44 */

bool FUN_0004b9b2(int *param_1,int *param_2)

{
  if (param_1 == (int *)0x0) {
    param_1 = (int *)*param_2;
  }
  do {
    param_1 = (int *)*param_1;
    if (param_1 == (int *)0x0) {
      return true;
    }
  } while (param_1[3] == 0);
  param_2[3] = 0;
  (*(code *)param_1[3])(param_1,param_2);
  return (*(byte *)(param_2 + 6) & 1) == 0;
}

