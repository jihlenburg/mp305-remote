/* Address: 0004f400; name: FUN_0004f400; body bytes: 46 */

int FUN_0004f400(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_1 == (int *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar2 = *param_1;
  while( true ) {
    if (iVar2 == 0) {
      return 0;
    }
    iVar1 = (*(code *)param_1[1])(param_2,*(undefined4 *)(iVar2 + 0x10));
    if (iVar1 == 0) break;
    if (iVar1 < 0) {
      iVar2 = *(int *)(iVar2 + 4);
    }
    else {
      iVar2 = *(int *)(iVar2 + 8);
    }
  }
  return iVar2;
}

