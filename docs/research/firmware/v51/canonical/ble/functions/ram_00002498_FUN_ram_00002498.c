/* Address: ram:00002498; name: FUN_ram_00002498; body bytes: 166 */

void FUN_ram_00002498(uint param_1,undefined4 param_2)

{
  gp = &DAT_ram_20002000;
  switch(param_2) {
  case 0:
    DAT_ram_400010b4 = DAT_ram_400010b4 & ~param_1;
    break;
  case 1:
    DAT_ram_400010b4 = DAT_ram_400010b4 & ~param_1;
    DAT_ram_400010b0 = param_1 | DAT_ram_400010b0;
    DAT_ram_400010a0 = ~param_1 & DAT_ram_400010a0;
    return;
  case 2:
    DAT_ram_400010b4 = DAT_ram_400010b4 | param_1;
    break;
  case 3:
    DAT_ram_400010b4 = ~param_1 & DAT_ram_400010b4;
    goto LAB_ram_00002526;
  case 4:
    DAT_ram_400010b4 = DAT_ram_400010b4 | param_1;
LAB_ram_00002526:
    DAT_ram_400010a0 = param_1 | DAT_ram_400010a0;
  default:
    goto switchD_ram_000024ae_default;
  }
  DAT_ram_400010b0 = DAT_ram_400010b0 & ~param_1;
  DAT_ram_400010a0 = ~param_1 & DAT_ram_400010a0;
switchD_ram_000024ae_default:
  return;
}

