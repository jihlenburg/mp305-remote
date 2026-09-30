/* Address: 00035c9c; name: FUN_00035c9c; body bytes: 110 */

void FUN_00035c9c(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_2 != 0) {
    iVar1 = FUN_0004f400();
    if (iVar1 != 0) {
      uVar3 = *(undefined4 *)(iVar1 + 0x10);
      (**(code **)(param_1 + 0x18))(uVar3,param_3);
      iVar2 = (**(code **)(param_1 + 0x3c))(uVar3);
      *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) - iVar2;
      uVar3 = FUN_0003f174(uVar3,*(undefined4 *)(param_1 + 4));
      uVar4 = *(undefined4 *)(*(int *)(iVar1 + 0x10) + *(int *)(param_1 + 0x2c) + -4);
      FUN_0004f4fc(param_1 + 0x24,iVar1);
      FUN_0003f158(uVar3);
      FUN_0004a2ac(param_1 + 0x30,uVar4);
      FUN_00046bec(uVar4);
      return;
    }
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

