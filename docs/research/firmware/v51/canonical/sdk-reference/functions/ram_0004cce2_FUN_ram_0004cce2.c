/* Address: ram:0004cce2; name: FUN_ram_0004cce2; body bytes: 94 */

undefined4 FUN_ram_0004cce2(undefined2 *param_1,undefined2 *param_2,int param_3)

{
  gp = 0x20004000;
  if (param_3 == 10) {
    *param_1 = *param_2;
    param_1[1] = param_2[1];
    param_1[2] = param_2[2];
    param_1[3] = param_2[3];
    param_1[4] = param_2[4];
    return 0;
  }
  return 1;
}

