/* Address: 0004a040; name: FUN_0004a040; body bytes: 78 */

undefined4 FUN_0004a040(undefined4 param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = FUN_0004b144(&DAT_0007ab6c,param_1);
  FUN_0004b210();
  FUN_0004e624(uVar1,0);
  if (param_2 != 0) {
    uVar2 = FUN_00047698(uVar1);
    FUN_00047d8e(uVar2,param_2);
  }
  if (param_3 != 0) {
    uVar2 = FUN_00048d88(uVar1);
    FUN_00049974(uVar2,param_3);
    FUN_000498fc(uVar2,3);
    FUN_0004e63c(uVar2,1);
  }
  return uVar1;
}

