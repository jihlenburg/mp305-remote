/* Address: 0004e44e; name: FUN_0004e44e; body bytes: 72 */

int FUN_0004e44e(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  if (param_2 != 0 || param_3 != 0) {
    FUN_0004af28(param_1);
    *(int *)(*(int *)(param_1 + 8) + 0x18) = *(int *)(*(int *)(param_1 + 8) + 0x18) + param_2;
    *(int *)(*(int *)(param_1 + 8) + 0x1c) = *(int *)(*(int *)(param_1 + 8) + 0x1c) + param_3;
    FUN_0004d528(param_1,param_2,param_3,1);
    iVar1 = FUN_0004e5a6(param_1,0xc,0);
    if (iVar1 != 1) {
      return iVar1;
    }
    FUN_0004d3d8(param_1);
  }
  return 1;
}

