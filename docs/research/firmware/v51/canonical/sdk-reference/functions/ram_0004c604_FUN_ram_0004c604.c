/* Address: ram:0004c604; name: FUN_ram_0004c604; body bytes: 30 */

void FUN_ram_0004c604(int param_1)

{
  gp = 0x20004000;
  FUN_ram_00042494(*(undefined1 *)(param_1 + 9));
  *(undefined1 *)(param_1 + 9) = 0xff;
  return;
}

