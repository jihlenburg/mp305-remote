/* Address: ram:0000253e; name: FUN_ram_0000253e; body bytes: 166 */

void FUN_ram_0000253e(uint param_1,undefined4 param_2)

{
  gp = &DAT_ram_20002000;
  switch(param_2) {
  case 0:
    DAT_ram_400010d4 = DAT_ram_400010d4 & ~param_1;
    break;
  case 1:
    DAT_ram_400010d4 = DAT_ram_400010d4 & ~param_1;
    DAT_ram_400010d0 = param_1 | DAT_ram_400010d0;
    DAT_ram_400010c0 = ~param_1 & DAT_ram_400010c0;
    return;
  case 2:
    DAT_ram_400010d4 = DAT_ram_400010d4 | param_1;
    break;
  case 3:
    DAT_ram_400010d4 = ~param_1 & DAT_ram_400010d4;
    goto LAB_ram_000025cc;
  case 4:
    DAT_ram_400010d4 = DAT_ram_400010d4 | param_1;
LAB_ram_000025cc:
    DAT_ram_400010c0 = param_1 | DAT_ram_400010c0;
  default:
    goto switchD_ram_00002554_default;
  }
  DAT_ram_400010d0 = DAT_ram_400010d0 & ~param_1;
  DAT_ram_400010c0 = ~param_1 & DAT_ram_400010c0;
switchD_ram_00002554_default:
  return;
}

