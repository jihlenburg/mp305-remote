/* Address: 00016538; name: FUN_00016538; body bytes: 102 */

void FUN_00016538(void)

{
  int iVar1;
  undefined1 uVar2;
  
  if ((1 < DAT_1fff8f48) && (DAT_1fff8f54 == DAT_1fff8f48 - 2)) {
    FUN_000166dc(&DAT_4004e400,0x400);
  }
  if (DAT_1fff8f54 == DAT_1fff8f48 - 1) {
    FUN_00016988(&DAT_4004e400,0x10,1);
    FUN_00016988(&DAT_4004e400,0x40,0);
    FUN_00016928(&DAT_4004e400);
    FUN_000166dc(&DAT_4004e400,0);
  }
  iVar1 = DAT_1fff8f44;
  uVar2 = FUN_00016a68(&DAT_4004e400);
  if (DAT_1fff8f48 <= DAT_1fff8f54) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  *(undefined1 *)(iVar1 + DAT_1fff8f54) = uVar2;
  DAT_1fff8f54 = DAT_1fff8f54 + 1;
  return;
}

