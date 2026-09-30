/* Address: ram:00042570; name: FUN_ram_00042570; body bytes: 22 */

void FUN_ram_00042570(undefined4 param_1,uint param_2)

{
  gp = 0x20004000;
  if (param_2 < 7) {
    (&DAT_ram_20001b94)[param_2] = param_1;
  }
  return;
}

