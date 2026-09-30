/* Address: 0004af28; name: FUN_0004af28; body bytes: 40 */

void FUN_0004af28(int param_1)

{
  ushort uVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 8) == 0) {
    iVar2 = FUN_0004a360(0x2c);
    *(int *)(param_1 + 8) = iVar2;
    if (iVar2 == 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    uVar1 = *(ushort *)(iVar2 + 0x2a);
    *(ushort *)(iVar2 + 0x2a) = uVar1 | 0x3c0;
    *(ushort *)(*(int *)(param_1 + 8) + 0x2a) = uVar1 | 0x3c3;
  }
  return;
}

