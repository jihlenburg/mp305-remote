/* Address: 0004669c; name: FUN_0004669c; body bytes: 18 */

undefined4 FUN_0004669c(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  if (param_1 != 0) {
    puVar1 = (undefined4 *)FUN_0003de0e();
    uVar2 = 0;
    if (puVar1 != (undefined4 *)0x0) {
      uVar2 = *puVar1;
    }
    return uVar2;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

