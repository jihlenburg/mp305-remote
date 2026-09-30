/* Address: ram:00003f20; name: FUN_ram_00003f20; body bytes: 26 */

undefined4 FUN_ram_00003f20(int param_1)

{
  gp = &DAT_ram_20002000;
  if (*(char *)(param_1 + 1) == -0x50) {
    DAT_ram_20004c09 = 1;
  }
  return 0;
}

