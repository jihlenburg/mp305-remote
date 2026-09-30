/* Address: ram:00008bf6; name: FUN_ram_00008bf6; body bytes: 48 */

void FUN_ram_00008bf6(int *param_1,undefined4 param_2)

{
  int iVar1;
  
  gp = &DAT_ram_20002000;
  DAT_ram_20006dec = 0;
  iVar1 = FUN_ram_00008d0e(param_2);
  if ((iVar1 == -1) && (DAT_ram_20006dec != 0)) {
    *param_1 = DAT_ram_20006dec;
  }
  return;
}

