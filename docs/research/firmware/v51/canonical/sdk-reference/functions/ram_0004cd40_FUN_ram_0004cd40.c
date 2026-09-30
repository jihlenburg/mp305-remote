/* Address: ram:0004cd40; name: FUN_ram_0004cd40; body bytes: 34 */

void FUN_ram_0004cd40(undefined1 *param_1,undefined1 *param_2)

{
  gp = 0x20004000;
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  *(undefined2 *)(param_1 + 2) = *(undefined2 *)(param_2 + 2);
  return;
}

