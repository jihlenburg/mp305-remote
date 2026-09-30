/* Address: 0004a3c4; name: FUN_0004a3c4; body bytes: 54 */

void FUN_0004a3c4(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  DAT_2003a5d8 = FUN_00052b7c(&DAT_1fffbc20,0x3e800);
  FUN_0004a152(&DAT_2003a5e4,4);
  puVar1 = (undefined4 *)FUN_0004a200(&DAT_2003a5e4);
  if (puVar1 != (undefined4 *)0x0) {
    uVar2 = FUN_00052bf0(DAT_2003a5d8);
    *puVar1 = uVar2;
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

