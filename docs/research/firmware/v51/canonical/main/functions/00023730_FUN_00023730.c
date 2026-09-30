/* Address: 00023730; name: FUN_00023730; body bytes: 124 */

void FUN_00023730(int param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  iVar4 = 0;
  *(undefined4 *)(param_1 + 0x3c) = 1;
  while ((pcVar2 = *(char **)(param_2 + iVar4 * 4), pcVar2 != (char *)0x0 && (*pcVar2 != '\0'))) {
    iVar1 = thunk_FUN_00050a1a(pcVar2,&LAB_0003ecc0);
    if (iVar1 == 0) {
      *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + 1;
    }
    else {
      iVar3 = iVar3 + 1;
    }
    iVar4 = iVar4 + 1;
  }
  if (*(int *)(param_1 + 0x38) != iVar3) {
    if (*(int *)(param_1 + 0x30) != 0) {
      FUN_00046bec();
      *(undefined4 *)(param_1 + 0x30) = 0;
    }
    if (*(int *)(param_1 + 0x34) != 0) {
      FUN_00046bec();
      *(undefined4 *)(param_1 + 0x34) = 0;
    }
    iVar4 = FUN_0004a318(iVar3 << 4);
    *(int *)(param_1 + 0x30) = iVar4;
    if (iVar4 == 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar4 = FUN_0004a318(iVar3 << 1);
    *(int *)(param_1 + 0x34) = iVar4;
    if (iVar4 == 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (*(int *)(param_1 + 0x30) == 0) {
      iVar3 = 0;
    }
    FUN_0004a57a(iVar4,0,iVar3 << 1);
    *(int *)(param_1 + 0x38) = iVar3;
  }
  return;
}

