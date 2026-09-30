/* Address: 000476f0; name: FUN_000476f0; body bytes: 50 */

void FUN_000476f0(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    if (*(code **)(iVar1 + 0xc) != (code *)0x0) {
      (**(code **)(iVar1 + 0xc))(iVar1,param_1);
    }
    iVar1 = FUN_00047614();
    if (((iVar1 != 0) && (param_1[0x10] != 0)) && (param_1[0x11] != 0)) {
      FUN_0003f1ca(param_1[0x10],param_1[0x11],0);
      return;
    }
  }
  return;
}

