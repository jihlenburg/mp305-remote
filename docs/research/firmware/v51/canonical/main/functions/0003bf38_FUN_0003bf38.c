/* Address: 0003bf38; name: FUN_0003bf38; body bytes: 42 */

void FUN_0003bf38(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar1 = FUN_0003db0a(param_1 + 1);
  uVar2 = FUN_0003db28(param_1 + 1);
  iVar3 = FUN_0004173e(*param_1,*(undefined1 *)(param_1 + 5),uVar2,uVar1,param_2);
  if (iVar3 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return;
}

