/* Address: 00035c48; name: FUN_00035c48; body bytes: 84 */

/* Recovered from stored Thumb pointer at 0007a528; callback identification is inferred until
   reviewed. */

void FUN_00035c48(int param_1,undefined4 param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_1 != 0) {
    for (piVar1 = (int *)FUN_0004a118(); piVar1 != (int *)0x0;
        piVar1 = (int *)FUN_0004a13c(param_1 + 0x30,piVar1)) {
      uVar3 = *(undefined4 *)(*piVar1 + 0x10);
      FUN_0003f174(uVar3,*(undefined4 *)(param_1 + 4));
      iVar2 = FUN_0003f17c();
      if (iVar2 == 0) {
        (**(code **)(param_1 + 0x18))(uVar3,param_2);
      }
    }
    FUN_0004f3a4(param_1 + 0x24);
    FUN_0004a0d8(param_1 + 0x30);
    *(undefined4 *)(param_1 + 0xc) = 0;
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

