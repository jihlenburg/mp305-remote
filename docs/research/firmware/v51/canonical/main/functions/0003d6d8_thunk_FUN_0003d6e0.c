/* Address: 0003d6d8; name: thunk_FUN_0003d6e0; body bytes: 2 */

void thunk_FUN_0003d6e0(int param_1,int param_2)

{
  for (; param_2 < 0; param_2 = param_2 + 0x168) {
  }
  for (; 0x167 < param_2; param_2 = param_2 + -0x168) {
  }
  *(int *)(param_1 + 0x2c) = param_2;
  FUN_0004d3d8();
  return;
}

