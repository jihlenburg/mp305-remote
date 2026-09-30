/* Address: 0002154a; name: FUN_0002154a; body bytes: 22 */

/* Recovered from stored Thumb pointer at 00020030; callback identification is inferred until
   reviewed. */

void FUN_0002154a(undefined1 param_1,undefined4 *param_2)

{
  undefined1 *puVar1;
  
  if (param_2[1] != 0) {
    puVar1 = (undefined1 *)*param_2;
    *param_2 = puVar1 + 1;
    *puVar1 = param_1;
    param_2[1] = param_2[1] + -1;
  }
  return;
}

