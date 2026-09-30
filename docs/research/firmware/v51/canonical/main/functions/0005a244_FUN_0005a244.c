/* Address: 0005a244; name: FUN_0005a244; body bytes: 42 */

void FUN_0005a244(int *param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)param_2[1];
  param_2[1] = piVar1[2];
  if ((int *)piVar1[2] != (int *)0x0) {
    *(int *)piVar1[2] = (int)param_2;
  }
  *piVar1 = *param_2;
  iVar2 = *param_2;
  if (iVar2 == 0) {
    *param_1 = (int)piVar1;
  }
  else if (*(int **)(iVar2 + 8) == param_2) {
    *(int **)(iVar2 + 8) = piVar1;
  }
  else {
    *(int **)(iVar2 + 4) = piVar1;
  }
  piVar1[2] = (int)param_2;
  *param_2 = (int)piVar1;
  return;
}

