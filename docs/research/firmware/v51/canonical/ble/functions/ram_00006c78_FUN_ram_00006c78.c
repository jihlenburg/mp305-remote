/* Address: ram:00006c78; name: FUN_ram_00006c78; body bytes: 54 */

void FUN_ram_00006c78(uint param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  gp = &DAT_ram_20002000;
  if (DAT_ram_20002ffc == param_1) {
    DAT_ram_20002fb1 = (undefined1)param_4;
    DAT_ram_20002fb2 = (undefined1)param_2;
    DAT_ram_20002ffe = param_2;
    DAT_ram_20003000 = param_3;
    DAT_ram_20003002 = param_4;
  }
  return;
}

