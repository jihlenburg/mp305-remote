/* Address: ram:00044398; name: FUN_ram_00044398; body bytes: 32 */

undefined * FUN_ram_00044398(int param_1)

{
  gp = 0x20004000;
  if ((param_1 == 0) && (DAT_ram_20001c06 != '\0')) {
    return &DAT_ram_200019d8;
  }
  return &DAT_ram_20001c1c;
}

