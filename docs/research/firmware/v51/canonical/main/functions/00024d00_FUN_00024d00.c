/* Address: 00024d00; name: FUN_00024d00; body bytes: 80 */

int FUN_00024d00(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = 0;
  if (param_2 != 0) {
    if (param_3 == 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if ((*(byte *)(param_2 + 4) & 1) == 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    iVar1 = FUN_00024b56(param_2,param_3);
    if (iVar1 != 0) {
      iVar1 = FUN_00024d72(param_2,param_3);
      FUN_00024bd4(param_2);
      *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 2;
      FUN_00024b6a(param_1,iVar1);
    }
    FUN_00024c9a(param_2);
    iVar1 = param_2 + 8;
  }
  return iVar1;
}

