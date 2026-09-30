/* Address: 0003f054; name: FUN_0003f054; body bytes: 74 */

int FUN_0003f054(int *param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  if (param_1 == (int *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_2 != 0) {
    FUN_0004aa44();
    if (param_1[3] == 0) {
      FUN_0004aa48(param_1 + 7);
      iVar1 = 0;
    }
    else {
      iVar1 = (**(code **)(*param_1 + 0xc))(param_1,param_2,param_3);
      if (iVar1 != 0) {
        FUN_0003f130();
      }
      FUN_0004aa48(param_1 + 7);
    }
    return iVar1;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

