/* Address: 000467c6; name: FUN_000467c6; body bytes: 74 */

void FUN_000467c6(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (param_1 != (int *)0x0) {
    iVar1 = FUN_0003df08();
    iVar2 = FUN_0003de3c(param_1);
    for (iVar3 = 0; iVar3 < iVar1; iVar3 = iVar3 + 1) {
      FUN_00046bec(*(undefined4 *)(iVar2 + iVar3 * 4));
    }
    if (*param_1 != 0) {
      FUN_00046bec();
      *param_1 = 0;
    }
    param_1[1] = 0;
    param_1[2] = 0;
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

