/* Address: 00010c5e; name: FUN_00010c5e; body bytes: 34 */

/* Recovered from stored Thumb pointer at 00010584; callback identification is inferred until
   reviewed. */

undefined4 FUN_00010c5e(int *param_1)

{
  if (((param_1[1] != 0) && (param_1[3] == 0)) && (param_1[2] != *param_1)) {
    *param_1 = *param_1 + -1;
    param_1[1] = param_1[1] + 1;
    return 0;
  }
  return 0xffffffff;
}

