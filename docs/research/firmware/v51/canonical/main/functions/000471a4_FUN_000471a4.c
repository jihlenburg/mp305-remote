/* Address: 000471a4; name: FUN_000471a4; body bytes: 46 */

int FUN_000471a4(void)

{
  int iVar1;
  
  iVar1 = FUN_0004a162(&DAT_2003a454);
  if (iVar1 != 0) {
    FUN_0004a152(iVar1,4);
    *(undefined4 *)(iVar1 + 0xc) = 0;
    *(undefined4 *)(iVar1 + 0x10) = 0;
    *(undefined4 *)(iVar1 + 0x14) = 0;
    *(byte *)(iVar1 + 0x1c) = *(byte *)(iVar1 + 0x1c) & 0xfc | 0xc;
    *(undefined4 *)(iVar1 + 0x18) = 0;
    return iVar1;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

