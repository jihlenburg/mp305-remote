/* Address: ram:00004dd8; name: thunk_FUN_ram_00002914; body bytes: 4 */

void thunk_FUN_ram_00002914(undefined1 *param_1,uint param_2)

{
  gp = &DAT_ram_20002000;
  while (param_2 != 0) {
    if (DAT_ram_4000340b != '\b') {
      DAT_ram_40003408 = *param_1;
      param_2 = param_2 - 1 & 0xffff;
      param_1 = param_1 + 1;
    }
  }
  return;
}

