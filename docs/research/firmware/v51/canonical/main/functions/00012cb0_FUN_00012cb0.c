/* Address: 00012cb0; name: FUN_00012cb0; body bytes: 56 */

void FUN_00012cb0(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00015ee8();
  if (param_1 == 0) {
    iVar2 = FUN_00016c0e(&DAT_1fff8f64,DAT_1fff8f64,param_2,param_3);
  }
  else {
    iVar2 = FUN_0001bcba(param_2,param_3);
  }
  if ((*(int *)(iVar1 + 0x20) == 0) && (iVar2 != 0)) {
    *(int *)(iVar1 + 0x20) = iVar2;
  }
  return;
}

