/* Address: ram:0005cde4; name: FUN_ram_0005cde4; body bytes: 28 */

bool FUN_ram_0005cde4(int param_1)

{
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x15) = 0;
  *(byte *)(param_1 + 0xc) = *(byte *)(param_1 + 0xc) & 0xfc | 1;
  return *(int *)(param_1 + 0x110) == 0;
}

