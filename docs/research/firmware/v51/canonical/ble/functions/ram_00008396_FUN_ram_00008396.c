/* Address: ram:00008396; name: FUN_ram_00008396; body bytes: 42 */

int FUN_ram_00008396(undefined4 param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  undefined1 *puVar2;
  
  gp = &DAT_ram_20002000;
  iVar1 = param_3[2] + -1;
  param_3[2] = iVar1;
  if ((iVar1 < 0) && ((iVar1 < (int)param_3[6] || (param_2 == 10)))) {
    iVar1 = FUN_ram_00007ac2();
    return iVar1;
  }
  puVar2 = (undefined1 *)*param_3;
  *param_3 = puVar2 + 1;
  *puVar2 = (char)param_2;
  return param_2;
}

