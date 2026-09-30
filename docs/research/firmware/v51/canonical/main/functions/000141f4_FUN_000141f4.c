/* Address: 000141f4; name: FUN_000141f4; body bytes: 14 */

undefined4 FUN_000141f4(undefined4 *param_1)

{
  *(undefined2 *)(param_1 + 1) = 0;
  *(undefined2 *)(param_1 + 7) = 0;
  *(undefined2 *)((int)param_1 + 6) = 0;
  *param_1 = 0;
  return 0;
}

