/* Address: ram:00003144; name: FUN_ram_00003144; body bytes: 18 */

undefined4 FUN_ram_00003144(int param_1)

{
  gp = &DAT_ram_20002000;
  if (param_1 != 0) {
    DAT_ram_20002f70 = param_1;
    return 0;
  }
  return 0x11;
}

