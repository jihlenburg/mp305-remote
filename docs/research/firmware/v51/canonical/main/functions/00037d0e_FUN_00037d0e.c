/* Address: 00037d0e; name: FUN_00037d0e; body bytes: 60 */

undefined4 FUN_00037d0e(int param_1)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  piVar1 = (int *)FUN_0004a14a();
  while( true ) {
    if (piVar1 == (int *)0x0) {
      return 0;
    }
    uVar2 = FUN_0003f174(*(undefined4 *)(*piVar1 + 0x10),*(undefined4 *)(param_1 + 4));
    iVar3 = FUN_0003f17c();
    if (iVar3 == 0) break;
    piVar1 = (int *)FUN_0004a144(param_1 + 0x30,piVar1);
  }
  return uVar2;
}

