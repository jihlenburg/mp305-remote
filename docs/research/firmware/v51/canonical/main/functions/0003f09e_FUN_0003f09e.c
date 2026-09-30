/* Address: 0003f09e; name: FUN_0003f09e; body bytes: 72 */

int FUN_0003f09e(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_2 != 0) {
    FUN_0004aa44();
    if (*(int *)(param_1 + 8) == 0) {
      FUN_0004aa48(param_1 + 0x1c);
      iVar1 = 0;
    }
    else {
      iVar1 = FUN_00025050(param_1,param_2,param_3);
      if (iVar1 != 0) {
        FUN_0003f130();
      }
      FUN_0004aa48(param_1 + 0x1c);
    }
    return iVar1;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

