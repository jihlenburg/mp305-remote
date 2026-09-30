/* Address: 0005b1e8; name: FUN_0005b1e8; body bytes: 66 */

void FUN_0005b1e8(int param_1,int param_2,uint param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_2 + 8);
  iVar3 = *(int *)(param_2 + 0xc);
  if (iVar3 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (iVar1 != 0) {
    *(int *)(iVar1 + 0xc) = iVar3;
    *(int *)(iVar3 + 8) = iVar1;
    iVar3 = param_1 + param_3 * 0x80 + param_4 * 4;
    if (((*(int *)(iVar3 + 0x44) == param_2) && (*(int *)(iVar3 + 0x44) = iVar1, iVar1 == param_1))
       && (iVar1 = param_1 + param_3 * 4, uVar2 = *(uint *)(iVar1 + 0x14) & ~(1 << (param_4 & 0xff))
          , *(uint *)(iVar1 + 0x14) = uVar2, uVar2 == 0)) {
      *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) & ~(1 << (param_3 & 0xff));
    }
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

