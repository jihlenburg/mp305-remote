/* Address: 00051b74; name: FUN_00051b74; body bytes: 50 */

int FUN_00051b74(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00052dc8(0,0,param_1,param_2);
  iVar2 = FUN_0004a318(iVar1 + 1);
  if (iVar2 != 0) {
    FUN_00052dc8(iVar2,iVar1 + 1,param_1,param_2);
    return iVar2;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

