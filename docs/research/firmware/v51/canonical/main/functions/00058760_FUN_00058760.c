/* Address: 00058760; name: FUN_00058760; body bytes: 76 */

void FUN_00058760(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = FUN_000408ec();
  DAT_2003a474 = FUN_000487b0(uVar1,param_2);
  if (DAT_2003a474 == 0) {
    uVar1 = FUN_00040900(param_1);
    DAT_2003a474 = FUN_000487b0(uVar1,param_2);
    if (DAT_2003a474 == 0) {
      uVar1 = FUN_00040928(param_1);
      DAT_2003a474 = FUN_000487b0(uVar1,param_2);
      if (DAT_2003a474 == 0) {
        uVar1 = FUN_000408d8(param_1);
        DAT_2003a474 = FUN_000487b0(uVar1,param_2);
      }
    }
  }
  return;
}

