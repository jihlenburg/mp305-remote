/* Address: ram:00058d50; name: FUN_ram_00058d50; body bytes: 66 */

void FUN_ram_00058d50(int param_1)

{
  gp = 0x20004000;
  tmos_stop_task(DAT_ram_20001b67,0x10);
  tmos_stop_task(DAT_ram_20001b67,0x20);
  DAT_ram_20001e9b = 0;
  *(undefined1 *)(param_1 + 4) = 0;
  *(undefined2 *)(param_1 + 6) = 0;
  return;
}

