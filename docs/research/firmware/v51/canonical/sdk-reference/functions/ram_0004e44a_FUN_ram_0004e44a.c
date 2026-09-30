/* Address: ram:0004e44a; name: FUN_ram_0004e44a; body bytes: 58 */

void FUN_ram_0004e44a(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  gp = 0x20004000;
  iVar1 = GAP_GetParamValue(0x12);
  if (iVar1 != 0) {
    iVar2 = FUN_ram_0004df14(param_1);
    if (iVar2 != 0) {
      tmos_start_task(DAT_ram_20001d4f,*(undefined2 *)(iVar2 + 0x30),iVar1);
      return;
    }
  }
  return;
}

