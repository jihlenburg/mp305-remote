/* Address: ram:0004eb02; name: FUN_ram_0004eb02; body bytes: 52 */

undefined4 FUN_ram_0004eb02(int param_1,undefined1 *param_2)

{
  gp = 0x20004000;
  if ((param_1 != 0) && (param_2 != (undefined1 *)0x0)) {
    *param_2 = *(undefined1 *)(param_1 + 1);
    tmos_memcpy(param_2 + 1,param_1 + 2,6);
    return 0;
  }
  return 2;
}

