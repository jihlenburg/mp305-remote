/* Address: ram:0004eb60; name: FUN_ram_0004eb60; body bytes: 60 */

undefined4 FUN_ram_0004eb60(int param_1,undefined2 *param_2)

{
  gp = 0x20004000;
  if ((param_1 != 0) && (param_2 != (undefined2 *)0x0)) {
    *param_2 = *(undefined2 *)(param_1 + 1);
    tmos_memcpy(param_2 + 1,param_1 + 3,8);
    return 0;
  }
  return 2;
}

