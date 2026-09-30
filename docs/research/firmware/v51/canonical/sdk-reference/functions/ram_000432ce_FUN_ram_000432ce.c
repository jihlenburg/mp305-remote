/* Address: ram:000432ce; name: FUN_ram_000432ce; body bytes: 46 */

undefined4 FUN_ram_000432ce(undefined1 *param_1,int param_2,undefined1 *param_3)

{
  gp = 0x20004000;
  if (param_2 == 4) {
    *param_3 = *param_1;
    *(undefined2 *)(param_3 + 2) = *(undefined2 *)(param_1 + 1);
    param_3[4] = param_1[3];
    return 0;
  }
  return 4;
}

