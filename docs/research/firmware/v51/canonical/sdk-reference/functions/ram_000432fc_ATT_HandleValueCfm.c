/* Address: ram:000432fc; name: ATT_HandleValueCfm; body bytes: 46 */

int ATT_HandleValueCfm(undefined4 param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00043928(param_1,0);
  if ((iVar1 == 0) && (DAT_ram_200019d0 != (code *)0x0)) {
    (*DAT_ram_200019d0)(param_1,0x1e);
  }
  return iVar1;
}

