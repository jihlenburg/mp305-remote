/* Address: 0004fcde; name: FUN_0004fcde; body bytes: 30 */

void FUN_0004fcde(undefined4 *param_1,undefined1 *param_2,undefined4 param_3)

{
  if (param_1 != (undefined4 *)0x0) {
    if (param_2 == (undefined1 *)0x0) {
      *param_1 = param_3;
      return;
    }
    if (param_2 == (undefined1 *)0x20000) {
      param_1[1] = param_3;
      return;
    }
    if (param_2 == &LAB_00050000) {
      param_1[2] = param_3;
    }
  }
  return;
}

