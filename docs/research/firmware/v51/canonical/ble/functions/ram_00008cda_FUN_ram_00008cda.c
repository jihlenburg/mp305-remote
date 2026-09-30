/* Address: ram:00008cda; name: FUN_ram_00008cda; body bytes: 52 */

void FUN_ram_00008cda(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  gp = &DAT_ram_20002000;
  DAT_ram_20006dec = 0;
  iVar1 = FUN_ram_00008d4e(param_2,param_3,param_4);
  if ((iVar1 == -1) && (DAT_ram_20006dec != 0)) {
    *param_1 = DAT_ram_20006dec;
  }
  return;
}

