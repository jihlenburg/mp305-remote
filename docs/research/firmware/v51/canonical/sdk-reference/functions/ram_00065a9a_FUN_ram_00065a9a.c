/* Address: ram:00065a9a; name: FUN_ram_00065a9a; body bytes: 82 */

undefined4 FUN_ram_00065a9a(uint param_1,char param_2)

{
  gp = 0x20004000;
  if (param_1 == 0) {
    param_1 = 0x25;
    goto LAB_ram_00065aa8;
  }
  if (param_1 < 0xc) {
    param_1 = param_1 - 1;
  }
  else {
    if (param_1 == 0xc) {
      param_1 = 0x26;
      goto LAB_ram_00065aa8;
    }
    if (0x26 < param_1) {
      if (param_1 != 0x27) {
        return 0x12;
      }
      goto LAB_ram_00065aa8;
    }
    param_1 = param_1 - 2;
  }
  param_1 = param_1 & 0xff;
LAB_ram_00065aa8:
  FUN_ram_000622e8(param_1,param_2 + -1);
  return 0;
}

