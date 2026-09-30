/* Address: 0005b118; name: FUN_0005b118; body bytes: 86 */

void FUN_0005b118(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_2 != 0) {
    uVar1 = FUN_0003f16a(param_2);
    iVar2 = FUN_0004f400(param_1 + 0x24,uVar1);
    if (iVar2 != 0) {
      uVar3 = *(undefined4 *)(*(int *)(param_1 + 0x2c) + *(int *)(iVar2 + 0x10) + -4);
      FUN_0004f4fc(param_1 + 0x24);
      FUN_0004a2ac(param_1 + 0x30,uVar3);
      FUN_00046bec(uVar3);
      iVar2 = (**(code **)(param_1 + 0x3c))(uVar1);
      *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) - iVar2;
    }
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

