/* Address: 00052b98; name: FUN_00052b98; body bytes: 88 */

uint FUN_00052b98(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  
  uVar3 = 0;
  if (param_2 != 0) {
    piVar2 = (int *)(param_2 + -8);
    uVar3 = *(uint *)(param_2 + -4);
    if ((uVar3 & 1) != 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    FUN_00024c80(piVar2);
    if ((int)((uint)*(byte *)(param_2 + -4) << 0x1e) < 0) {
      iVar4 = *piVar2;
      if (iVar4 == 0) {
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      if ((*(byte *)(iVar4 + 4) & 1) == 0) {
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      FUN_00024d50(param_1,iVar4);
      piVar2 = (int *)FUN_00024b34(iVar4,piVar2);
    }
    uVar1 = FUN_00024cb4(param_1,piVar2);
    FUN_00024b6a(param_1,uVar1);
  }
  return uVar3;
}

