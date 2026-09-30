/* Address: 000656b6; name: FUN_000656b6; body bytes: 22 */

void FUN_000656b6(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + 2;
  param_1[1] = puVar1;
  param_1[2] = 0xffffffff;
  param_1[3] = puVar1;
  param_1[4] = puVar1;
  *param_1 = 0;
  return;
}

