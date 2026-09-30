/* Address: ram:00004e1a; name: FUN_ram_00004e1a; body bytes: 108 */

void FUN_ram_00004e1a(undefined1 *param_1,int param_2,int param_3)

{
  undefined1 *puVar1;
  
  gp = &DAT_ram_20002000;
  FUN_ram_00007968("Data-%x:");
  puVar1 = param_1 + param_2;
  if (param_3 == 99) {
    for (; param_1 != puVar1; param_1 = param_1 + 1) {
      FUN_ram_00007968(&DAT_ram_00008f18,*param_1);
    }
  }
  else {
    for (; param_1 != puVar1; param_1 = param_1 + 1) {
      FUN_ram_00007968(&DAT_ram_00008f1c,*param_1);
    }
  }
  FUN_ram_000079ac(10);
  return;
}

