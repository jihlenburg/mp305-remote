/* Address: ram:00007ed6; name: FUN_ram_00007ed6; body bytes: 106 */

void FUN_ram_00007ed6(undefined4 *param_1,undefined2 param_2,undefined2 param_3)

{
  gp = &DAT_ram_20002000;
  *(undefined2 *)(param_1 + 3) = param_2;
  *(undefined2 *)((int)param_1 + 0xe) = param_3;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[0x19] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  FUN_ram_00001d1a(param_1 + 0x17,0,8);
  param_1[9] = FUN_ram_00008b08;
  param_1[10] = &LAB_ram_00008b38;
  param_1[0xb] = FUN_ram_00008b86;
  param_1[8] = param_1;
  param_1[0xc] = &LAB_ram_00008bbc;
  return;
}

