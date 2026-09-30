/* Address: 0004c91e; name: FUN_0004c91e; body bytes: 6 */

undefined4 FUN_0004c91e(int param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uStack_10;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uStack_10 = 0;
  iVar1 = FUN_00037bd8(param_1,*(ushort *)(param_1 + 0x28) | param_2,0x10,&uStack_10);
  if (iVar1 != 1) {
    uVar2 = FUN_00050b1c(0x10);
    return uVar2;
  }
  return uStack_10;
}

