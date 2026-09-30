/* Address: ram:00048886; name: FUN_ram_00048886; body bytes: 50 */

void FUN_ram_00048886(char *param_1)

{
  gp = 0x20004000;
  if (param_1 != (char *)0x0) {
    if (1 < (byte)(*param_1 + 2U)) {
      FUN_ram_00042494(*param_1);
      *param_1 = -1;
      return;
    }
  }
  return;
}

