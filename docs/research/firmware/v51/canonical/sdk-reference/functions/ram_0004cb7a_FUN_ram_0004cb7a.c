/* Address: ram:0004cb7a; name: FUN_ram_0004cb7a; body bytes: 78 */

undefined4 FUN_ram_0004cb7a(undefined2 *param_1,undefined2 *param_2,int param_3)

{
  gp = 0x20004000;
  if (param_3 == 8) {
    *param_1 = *param_2;
    param_1[1] = param_2[1];
    param_1[2] = param_2[2];
    param_1[3] = param_2[3];
    return 0;
  }
  return 1;
}

