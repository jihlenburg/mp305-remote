/* Address: 000414c8; name: FUN_000414c8; body bytes: 86 */

int FUN_000414c8(ushort *param_1,int param_2,int param_3)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  
  if (param_1 == (ushort *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar1 = *param_1 >> 8;
  if (uVar1 == 7) {
    iVar3 = 2;
  }
  else if (uVar1 == 8) {
    iVar3 = 4;
  }
  else if (uVar1 == 9) {
    iVar3 = 0x10;
  }
  else if (uVar1 == 10) {
    iVar3 = 0x100;
  }
  else {
    iVar3 = 0;
  }
  iVar3 = (uint)param_1[4] * param_3 + *(int *)(param_1 + 8) + iVar3 * 4;
  if (param_2 != 0) {
    iVar2 = FUN_00040314();
    return iVar3 + ((uint)(param_2 * iVar2) >> 3);
  }
  return iVar3;
}

