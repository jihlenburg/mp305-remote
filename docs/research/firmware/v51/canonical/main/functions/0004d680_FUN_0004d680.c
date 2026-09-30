/* Address: 0004d680; name: FUN_0004d680; body bytes: 134 */

void FUN_0004d680(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = FUN_0004bc8c();
  if (iVar1 != 0) {
    iVar2 = FUN_0004ba5c();
    iVar3 = FUN_0004bc12(param_1);
    if (iVar3 < 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if ((((-1 < param_2) || (param_2 = param_2 + iVar2, -1 < param_2)) && (param_2 < iVar2)) &&
       (param_2 != iVar3)) {
      if (param_2 < iVar3) {
        for (; param_2 < iVar3; iVar3 = iVar3 + -1) {
          *(undefined4 *)(**(int **)(iVar1 + 8) + iVar3 * 4) =
               *(undefined4 *)(**(int **)(iVar1 + 8) + iVar3 * 4 + -4);
        }
      }
      else {
        for (; iVar3 < param_2; iVar3 = iVar3 + 1) {
          *(undefined4 *)(**(int **)(iVar1 + 8) + iVar3 * 4) =
               *(undefined4 *)(**(int **)(iVar1 + 8) + iVar3 * 4 + 4);
        }
      }
      *(undefined4 *)(**(int **)(iVar1 + 8) + param_2 * 4) = param_1;
      FUN_0004e5a6(iVar1,0x27,0);
      FUN_0004d3d8(iVar1);
      return;
    }
  }
  return;
}

