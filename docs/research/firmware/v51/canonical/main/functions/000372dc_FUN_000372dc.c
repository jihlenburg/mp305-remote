/* Address: 000372dc; name: FUN_000372dc; body bytes: 24 */

void FUN_000372dc(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x48) == 0) {
    iVar1 = FUN_0004a360(0x44);
    if (iVar1 == 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    *(int *)(param_1 + 0x48) = iVar1;
  }
  return;
}

