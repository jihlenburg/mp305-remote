/* Address: ram:0004414c; name: FUN_ram_0004414c; body bytes: 22 */

bool FUN_ram_0004414c(int param_1)

{
  gp = 0x20004000;
  if (param_1 != 0) {
    return 0xe7 < (param_1 - 0x17U & 0xff);
  }
  return false;
}

