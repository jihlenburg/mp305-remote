/* Address: ram:00008c26; name: FUN_ram_00008c26; body bytes: 50 */

void FUN_ram_00008c26(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  gp = &DAT_ram_20002000;
  DAT_ram_20006dec = 0;
  iVar1 = FUN_ram_00008d1e(param_2,param_3);
  if ((iVar1 == -1) && (DAT_ram_20006dec != 0)) {
    *param_1 = DAT_ram_20006dec;
  }
  return;
}

