/* Address: 0004b42a; name: FUN_0004b42a; body bytes: 88 */

void FUN_0004b42a(undefined4 param_1,int param_2)

{
  int iVar1;
  
  FUN_00046760(param_2);
  FUN_0004b648(0);
  FUN_0004e210(param_2);
  FUN_0004b648(1);
  FUN_0003c97c(param_2,0);
  iVar1 = FUN_0004bbe2(param_2);
  if (iVar1 != 0) {
    FUN_0004737c(param_2);
  }
  if (*(int **)(param_2 + 8) != (int *)0x0) {
    if (**(int **)(param_2 + 8) != 0) {
      FUN_00046bec();
      **(undefined4 **)(param_2 + 8) = 0;
    }
    FUN_000467c6(*(int *)(param_2 + 8) + 8);
    FUN_00046bec(*(undefined4 *)(param_2 + 8));
    *(undefined4 *)(param_2 + 8) = 0;
  }
  return;
}

