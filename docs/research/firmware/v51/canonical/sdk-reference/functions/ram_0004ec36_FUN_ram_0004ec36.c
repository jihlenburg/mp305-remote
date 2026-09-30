/* Address: ram:0004ec36; name: FUN_ram_0004ec36; body bytes: 44 */

undefined4 FUN_ram_0004ec36(int param_1,int param_2)

{
  gp = 0x20004000;
  if (param_1 == 0) {
    return 2;
  }
  if (param_2 != 0) {
    tmos_memcpy(param_2,param_1 + 1,0x40);
    return 0;
  }
  return 2;
}

