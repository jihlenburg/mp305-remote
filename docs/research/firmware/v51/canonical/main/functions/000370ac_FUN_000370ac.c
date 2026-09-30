/* Address: 000370ac; name: FUN_000370ac; body bytes: 114 */

undefined4 FUN_000370ac(int param_1,int param_2)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_2 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  piVar1 = (int *)FUN_0004a118();
  if (piVar1 != (int *)0x0) {
    uVar4 = *(undefined4 *)(*piVar1 + 0x10);
    uVar2 = FUN_0003f174(uVar4,*(undefined4 *)(param_1 + 4));
    iVar3 = (**(code **)(param_1 + 0x10))(uVar4,param_2);
    if (iVar3 == 0) {
      return uVar2;
    }
  }
  iVar3 = FUN_0004f400(param_1 + 0x24,param_2);
  if (iVar3 == 0) {
    return 0;
  }
  uVar4 = *(undefined4 *)(*(int *)(param_1 + 0x2c) + *(int *)(iVar3 + 0x10) + -4);
  uVar2 = FUN_0004a118(param_1 + 0x30);
  FUN_0004a24e(param_1 + 0x30,uVar4,uVar2);
  uVar2 = FUN_0003f174(*(undefined4 *)(iVar3 + 0x10),*(undefined4 *)(param_1 + 4));
  return uVar2;
}

