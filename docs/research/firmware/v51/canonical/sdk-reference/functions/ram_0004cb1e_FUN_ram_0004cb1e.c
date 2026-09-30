/* Address: ram:0004cb1e; name: FUN_ram_0004cb1e; body bytes: 46 */

undefined4 FUN_ram_0004cb1e(undefined2 *param_1,undefined2 *param_2,int param_3)

{
  gp = 0x20004000;
  if (param_3 == 4) {
    *param_1 = *param_2;
    param_1[1] = param_2[1];
    return 0;
  }
  return 1;
}

