/* Address: 000599fc; name: FUN_000599fc; body bytes: 38 */

void FUN_000599fc(undefined4 *param_1,undefined4 param_2)

{
  uint uVar1;
  
  if (param_1[0x10] != 0) {
    uVar1 = param_1[3] + param_1[0x10];
    param_1[3] = uVar1;
    if ((uint)param_1[2] <= uVar1) {
      param_1[3] = *param_1;
    }
    FUN_0001046a(param_2);
    return;
  }
  return;
}

