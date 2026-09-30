/* Address: 00024cb4; name: FUN_00024cb4; body bytes: 54 */

int FUN_00024cb4(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = FUN_00024cea(param_2);
  if (iVar1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if ((*(byte *)(iVar1 + 4) & 1) != 0) {
    if (*(uint *)(param_2 + 4) >> 2 == 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    FUN_00024d50(param_1,iVar1);
    param_2 = FUN_00024b34(param_2,iVar1);
  }
  return param_2;
}

