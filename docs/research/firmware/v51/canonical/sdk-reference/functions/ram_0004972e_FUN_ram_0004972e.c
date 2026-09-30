/* Address: ram:0004972e; name: FUN_ram_0004972e; body bytes: 114 */

void FUN_ram_0004972e(int param_1,int param_2,undefined1 param_3,undefined4 param_4,int param_5)

{
  gp = 0x20004000;
  if (param_5 == 0xff) {
    return;
  }
  FUN_ram_0004887a(&LAB_ram_000496d6,param_1,0x1e,param_1 + 8);
  *(char *)(param_1 + 9) = (char)param_5;
  *(undefined1 *)(param_1 + 2) = param_3;
  *(undefined4 *)(param_1 + 4) = param_4;
  if (param_2 != 0) {
    tmos_memcpy(param_1 + 0xc,param_2,0x18);
    return;
  }
  return;
}

