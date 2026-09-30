/* Address: ram:0005501c; name: FUN_ram_0005501c; body bytes: 92 */

void FUN_ram_0005501c(int param_1)

{
  gp = 0x20004000;
  FUN_ram_00062262();
  *(undefined1 *)(param_1 + 0xc) = 0;
  *(undefined1 *)(param_1 + 0xb) = 0;
  *(undefined1 *)(param_1 + 9) = 0;
  FUN_ram_00053848(param_1);
  tmos_stop_task(DAT_ram_20001b67,1);
  tmos_stop_task(DAT_ram_20001b67,2);
  if (*(char *)(param_1 + 0x16) != -1) {
    FUN_ram_00042494();
    *(undefined1 *)(param_1 + 0x16) = 0xff;
  }
  return;
}

