/* Address: ram:20000010; name: FUN_ram_20000010; body bytes: 1 */

void FUN_ram_20000010(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  gp = 0x20004000;
  if (param_3 < param_2) {
    return;
  }
  *param_2 = *param_1;
  FUN_ram_20000010(param_1 + 1);
  return;
}

