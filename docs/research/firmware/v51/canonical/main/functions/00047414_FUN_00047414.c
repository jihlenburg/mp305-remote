/* Address: 00047414; name: FUN_00047414; body bytes: 38 */

undefined4 FUN_00047414(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uStack_c;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uStack_c = param_2;
  iVar1 = FUN_000472e0();
  if ((iVar1 != 0) && (iVar2 = FUN_0004cd9c(iVar1,0x80), iVar2 == 0)) {
    uVar3 = FUN_0004e5a6(iVar1,0xe,&uStack_c);
    return uVar3;
  }
  return 1;
}

