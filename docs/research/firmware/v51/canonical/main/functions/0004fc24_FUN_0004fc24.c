/* Address: 0004fc24; name: FUN_0004fc24; body bytes: 46 */

void FUN_0004fc24(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  while (*(int *)(param_2 + 0x30) != 0) {
    uVar1 = FUN_0004a118(param_2 + 0x2c);
    FUN_0004a2ac(param_2 + 0x2c,uVar1);
    FUN_00046bec(uVar1);
  }
  FUN_0004a0d8();
  return;
}

