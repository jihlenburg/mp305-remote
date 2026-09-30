/* Address: 00024b6a; name: FUN_00024b6a; body bytes: 106 */

void FUN_00024b6a(int param_1,int param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint local_28;
  uint uStack_24;
  
  local_28 = param_3;
  uStack_24 = param_4;
  FUN_00053566(*(uint *)(param_2 + 4) & 0xfffffffc,&local_28,&uStack_24);
  uVar2 = uStack_24;
  uVar1 = local_28;
  iVar4 = param_1 + local_28 * 0x80 + uStack_24 * 4;
  iVar3 = *(int *)(iVar4 + 0x44);
  if (iVar3 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_2 != 0) {
    *(int *)(param_2 + 8) = iVar3;
    *(int *)(param_2 + 0xc) = param_1;
    *(int *)(iVar3 + 0xc) = param_2;
    iVar3 = FUN_00023690(param_2 + 8,4);
    if (param_2 + 8 != iVar3) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    *(int *)(iVar4 + 0x44) = param_2;
    *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | 1 << (uVar1 & 0xff);
    param_1 = param_1 + uVar1 * 4;
    *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) | 1 << (uVar2 & 0xff);
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

