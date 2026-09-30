/* Address: 000377d4; name: FUN_000377d4; body bytes: 38 */

undefined4 FUN_000377d4(int param_1,int param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  
  if (param_2 == 0) {
    iVar2 = *param_3 + 1;
    *param_3 = iVar2;
    piVar1 = *(int **)(param_1 + 8);
    if ((int)(uint)*(ushort *)(piVar1 + 10) <= iVar2) {
      return 0;
    }
  }
  else {
    iVar2 = *param_3 + -1;
    *param_3 = iVar2;
    if (iVar2 < 0) {
      return 0;
    }
    piVar1 = *(int **)(param_1 + 8);
  }
  return *(undefined4 *)(*piVar1 + iVar2 * 4);
}

