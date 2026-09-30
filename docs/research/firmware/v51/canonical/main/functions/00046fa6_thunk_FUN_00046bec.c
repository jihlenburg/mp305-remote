/* Address: 00046fa6; name: thunk_FUN_00046bec; body bytes: 4 */

void thunk_FUN_00046bec(undefined4 *param_1)

{
  uint uVar1;
  
  if ((param_1 != &DAT_2003a484) && (param_1 != (undefined4 *)0x0)) {
    uVar1 = FUN_00052b38();
    FUN_00052b98(DAT_2003a5d8,param_1);
    if (uVar1 < DAT_2003a5dc) {
      DAT_2003a5dc = DAT_2003a5dc - uVar1;
    }
    else {
      DAT_2003a5dc = 0;
    }
    return;
  }
  return;
}

