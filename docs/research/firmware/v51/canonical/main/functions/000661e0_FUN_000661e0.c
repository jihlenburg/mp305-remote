/* Address: 000661e0; name: FUN_000661e0; body bytes: 52 */

void FUN_000661e0(int param_1)

{
  FUN_00040acc(param_1,0x3c,0);
  if (*(code **)(param_1 + 0x2c) == (code *)0x0) {
    do {
    } while (*(int *)(param_1 + 0x30) != 0);
  }
  else {
    if (*(int *)(param_1 + 0x30) != 0) {
      (**(code **)(param_1 + 0x2c))(param_1);
    }
    *(undefined4 *)(param_1 + 0x30) = 0;
  }
  *(undefined4 *)(param_1 + 0x34) = 0;
  FUN_00040acc(param_1,0x3d,0);
  return;
}

