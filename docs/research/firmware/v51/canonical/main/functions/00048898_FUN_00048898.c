/* Address: 00048898; name: FUN_00048898; body bytes: 16 */

void FUN_00048898(undefined1 *param_1,undefined1 param_2)

{
  if (param_1 != (undefined1 *)0x0) {
    *param_1 = param_2;
    param_1[10] = param_1[10] | 2;
  }
  return;
}

