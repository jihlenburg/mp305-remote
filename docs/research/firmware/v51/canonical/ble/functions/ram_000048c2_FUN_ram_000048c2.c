/* Address: ram:000048c2; name: FUN_ram_000048c2; body bytes: 84 */

void FUN_ram_000048c2(int param_1,uint param_2)

{
  gp = &DAT_ram_20002000;
  if (param_2 == 0) {
    if (param_1 == 1) {
      DAT_ram_40005004 = 0;
      return;
    }
    if (param_1 == 8) {
      DAT_ram_40005007 = 0;
      return;
    }
    if (param_1 == 0x40) {
      DAT_ram_4000500a = 0;
    }
  }
  else if (((param_1 == 1) || (param_1 == 8)) || (param_1 == 0x40)) {
    FUN_ram_0000268a(param_1,param_2 & 0xff,1,1);
    return;
  }
  return;
}

