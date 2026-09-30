/* Address: 0004bc12; name: FUN_0004bc12; body bytes: 44 */

int FUN_0004bc12(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int extraout_r2;
  
  iVar1 = FUN_0004bc8c(param_1,param_2,param_1);
  if (iVar1 == 0) {
    iVar2 = -1;
  }
  else {
    iVar2 = 0;
    while( true ) {
      if ((int)(uint)*(ushort *)(*(int **)(iVar1 + 8) + 10) <= iVar2) {
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      if (*(int *)(**(int **)(iVar1 + 8) + iVar2 * 4) == extraout_r2) break;
      iVar2 = iVar2 + 1;
    }
  }
  return iVar2;
}

