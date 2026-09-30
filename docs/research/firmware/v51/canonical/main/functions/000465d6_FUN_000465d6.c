/* Address: 000465d6; name: FUN_000465d6; body bytes: 44 */

void FUN_000465d6(int param_1,uint param_2)

{
  if (*(uint *)(param_1 + 0x40) != param_2) {
    if (*(uint *)(param_1 + 0x3c) <= param_2) {
      param_2 = *(uint *)(param_1 + 0x3c) - 1;
    }
    *(uint *)(param_1 + 0x40) = param_2;
    *(uint *)(param_1 + 0x44) = param_2;
    if (*(int *)(param_1 + 0x2c) != 0) {
      FUN_00058850(param_1);
    }
    FUN_0004d3d8(param_1);
    return;
  }
  return;
}

