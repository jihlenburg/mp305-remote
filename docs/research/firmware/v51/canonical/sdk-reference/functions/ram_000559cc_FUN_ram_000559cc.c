/* Address: ram:000559cc; name: FUN_ram_000559cc; body bytes: 60 */

void FUN_ram_000559cc(int param_1,undefined4 param_2)

{
  gp = 0x20004000;
  if (*(char *)(param_1 + 0x27) != -1) {
    FUN_ram_00042494(*(char *)(param_1 + 0x27),param_2,param_2);
    *(undefined1 *)(param_1 + 0x27) = 0xff;
  }
  FUN_ram_00042362(&LAB_ram_00056d8e,param_1,param_2,param_1 + 0x27);
  return;
}

