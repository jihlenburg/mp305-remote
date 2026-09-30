/* Address: ram:00055dd2; name: FUN_ram_00055dd2; body bytes: 12 */

void FUN_ram_00055dd2(int param_1)

{
  gp = 0x20004000;
  *(byte *)(param_1 + 0xc) = *(byte *)(param_1 + 0xc) & 0xf3;
  return;
}

