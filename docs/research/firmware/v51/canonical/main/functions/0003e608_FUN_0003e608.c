/* Address: 0003e608; name: FUN_0003e608; body bytes: 48 */

void FUN_0003e608(void)

{
  int iVar1;
  
  iVar1 = FUN_00047724();
  if (iVar1 != 0) {
    FUN_00047908(iVar1,0x3e589);
    FUN_0004790c(iVar1,0x3e64d);
    FUN_00047904(iVar1,0x3e375);
    FUN_00047900(iVar1,0x3e355);
    *(undefined **)(iVar1 + 0x10) = &DAT_0003e648;
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

