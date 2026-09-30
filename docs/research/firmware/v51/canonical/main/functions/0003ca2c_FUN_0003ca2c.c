/* Address: 0003ca2c; name: FUN_0003ca2c; body bytes: 60 */

int FUN_0003ca2c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_0004a388(*(undefined4 *)(param_1 + 0x34),0,*(undefined4 *)(param_1 + 0x30),0,0x400);
  iVar2 = FUN_000405ba(uVar1,param_2,param_3,param_4,param_5);
  return *(int *)(param_1 + 0x24) +
         (iVar2 * (*(int *)(param_1 + 0x2c) - *(int *)(param_1 + 0x24)) >> 10);
}

