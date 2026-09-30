/* Address: ram:00055a08; name: FUN_ram_00055a08; body bytes: 60 */

void FUN_ram_00055a08(int param_1,undefined4 param_2)

{
  gp = 0x20004000;
  if (*(char *)(param_1 + 0x28) != -1) {
    FUN_ram_00042494(*(char *)(param_1 + 0x28),param_2,param_2);
    *(undefined1 *)(param_1 + 0x28) = 0xff;
  }
  FUN_ram_00042362(&LAB_ram_00056db8,param_1,param_2,param_1 + 0x28);
  return;
}

