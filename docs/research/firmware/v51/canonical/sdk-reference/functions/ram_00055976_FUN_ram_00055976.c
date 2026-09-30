/* Address: ram:00055976; name: FUN_ram_00055976; body bytes: 86 */

void FUN_ram_00055976(int param_1,undefined4 param_2)

{
  gp = 0x20004000;
  if (*(char *)(param_1 + 0x26) != -1) {
    FUN_ram_00042494(*(char *)(param_1 + 0x26),param_2,param_2);
    *(undefined1 *)(param_1 + 0x26) = 0xff;
  }
  *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 0x60;
  *(short *)(param_1 + 0x44) = *(short *)(param_1 + 0x3e) + *(short *)(param_1 + 0x46);
  FUN_ram_00042362(&LAB_ram_00055938,param_1,param_2,param_1 + 0x26);
  return;
}

