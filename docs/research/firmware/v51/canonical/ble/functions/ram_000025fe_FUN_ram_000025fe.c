/* Address: ram:000025fe; name: FUN_ram_000025fe; body bytes: 140 */

void FUN_ram_000025fe(undefined4 param_1)

{
  gp = &DAT_ram_20002000;
  switch(param_1) {
  case 0:
    DAT_ram_40005002 = DAT_ram_40005002 & 0xf0;
    break;
  case 1:
    DAT_ram_40005002 = DAT_ram_40005002 & 0xf0 | 1;
    break;
  case 2:
    DAT_ram_40005002 = DAT_ram_40005002 & 0xf0 | 4;
    break;
  case 3:
    DAT_ram_40005002 = DAT_ram_40005002 & 0xf0 | 5;
    break;
  case 4:
    DAT_ram_40005002 = DAT_ram_40005002 & 0xf0 | 8;
    break;
  case 5:
    DAT_ram_40005002 = DAT_ram_40005002 & 0xf0 | 9;
    break;
  case 6:
    DAT_ram_40005002 = DAT_ram_40005002 & 0xf0 | 0xc;
    break;
  case 7:
    DAT_ram_40005002 = DAT_ram_40005002 & 0xf0 | 0xd;
  }
  return;
}

