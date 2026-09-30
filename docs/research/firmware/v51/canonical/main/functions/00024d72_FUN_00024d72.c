/* Address: 00024d72; name: FUN_00024d72; body bytes: 108 */

int FUN_00024d72(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = param_1 + param_2 + 4;
  uVar3 = ((*(uint *)(param_1 + 4) & 0xfffffffc) - param_2) - 4;
  iVar1 = FUN_00023690(iVar2 + 8,4);
  if (iVar2 + 8 != iVar1) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if ((*(uint *)(param_1 + 4) & 0xfffffffc) != uVar3 + param_2 + 4) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  *(uint *)(iVar2 + 4) = *(byte *)(iVar2 + 4) & 3 | uVar3;
  if ((uVar3 & 0xfffffffc) < 0xc) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  *(uint *)(param_1 + 4) = *(byte *)(param_1 + 4) & 3 | param_2;
  FUN_00024c80(iVar2);
  return iVar2;
}

