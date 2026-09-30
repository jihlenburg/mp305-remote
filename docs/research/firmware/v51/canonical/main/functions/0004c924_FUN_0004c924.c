/* Address: 0004c924; name: FUN_0004c924; body bytes: 42 */

undefined4 FUN_0004c924(int param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_10;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  local_10 = 0;
  iVar1 = FUN_00037bd8(param_1,*(ushort *)(param_1 + 0x28) | param_2,param_3,&local_10);
  if (iVar1 != 1) {
    uVar2 = FUN_00050b1c(param_3);
    return uVar2;
  }
  return local_10;
}

