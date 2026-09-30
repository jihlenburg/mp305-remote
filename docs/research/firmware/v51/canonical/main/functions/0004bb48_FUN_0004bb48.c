/* Address: 0004bb48; name: FUN_0004bb48; body bytes: 62 */

void FUN_0004bb48(int param_1)

{
  int iVar1;
  uint uVar2;
  
  if (*(int *)(param_1 + 4) != 0) {
    param_1 = FUN_0004bc94();
  }
  iVar1 = FUN_0004a118(&DAT_2003a424);
  do {
    if (iVar1 == 0) {
      return;
    }
    for (uVar2 = 0; uVar2 < *(uint *)(iVar1 + 0x2d0); uVar2 = uVar2 + 1) {
      if (*(int *)(*(int *)(iVar1 + 0x2b4) + uVar2 * 4) == param_1) {
        return;
      }
    }
    iVar1 = FUN_0004a13c(&DAT_2003a424,iVar1);
  } while( true );
}

