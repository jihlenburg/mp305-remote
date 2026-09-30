/* Address: 0004a120; name: FUN_0004a120; body bytes: 28 */

int FUN_0004a120(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int extraout_r2;
  int extraout_r2_00;
  int iVar2;
  undefined4 extraout_r3;
  undefined4 extraout_r3_00;
  undefined4 uVar3;
  
  iVar1 = FUN_0004a118(param_1,param_2,0,param_1);
  iVar2 = extraout_r2;
  uVar3 = extraout_r3;
  while (iVar1 != 0) {
    iVar1 = FUN_0004a13c(uVar3,iVar1,iVar2 + 1);
    iVar2 = extraout_r2_00;
    uVar3 = extraout_r3_00;
  }
  return iVar2;
}

