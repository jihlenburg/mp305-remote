/* Address: ram:0004cbc8; name: FUN_ram_0004cbc8; body bytes: 30 */

undefined4 FUN_ram_0004cbc8(undefined2 *param_1,undefined2 *param_2,int param_3)

{
  gp = 0x20004000;
  if (param_3 == 2) {
    *param_1 = *param_2;
    return 0;
  }
  return 1;
}

