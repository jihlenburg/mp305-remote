/* Address: 0004ba04; name: FUN_0004ba04; body bytes: 88 */

undefined4 FUN_0004ba04(int param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = *(int **)(param_1 + 8);
  if (piVar2 != (int *)0x0) {
    if (param_2 < 0) {
      iVar1 = *(ushort *)(piVar2 + 10) - 1;
      param_2 = param_2 + 1;
      if (-1 < iVar1) {
        do {
          if (**(int **)(*piVar2 + iVar1 * 4) == param_3) {
            if (param_2 == 0) {
              return *(undefined4 *)(*piVar2 + iVar1 * 4);
            }
            param_2 = param_2 + 1;
          }
          iVar1 = iVar1 + -1;
        } while (-1 < iVar1);
      }
    }
    else {
      for (iVar1 = 0; iVar1 < (int)(uint)*(ushort *)(piVar2 + 10); iVar1 = iVar1 + 1) {
        if (**(int **)(*piVar2 + iVar1 * 4) == param_3) {
          if (param_2 == 0) {
            return *(undefined4 *)(*piVar2 + iVar1 * 4);
          }
          param_2 = param_2 + -1;
        }
      }
    }
  }
  return 0;
}

