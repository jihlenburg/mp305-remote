/* Address: 00049ab4; name: FUN_00049ab4; body bytes: 42 */

void FUN_00049ab4(void)

{
  DAT_2003a47c = FUN_0004a318(DAT_2003a478 << 3);
  FUN_0004687c();
  *(undefined4 *)(DAT_2003a47c + 0x10) = 0x38001;
  *(undefined4 *)(DAT_2003a47c + 0x14) = 0;
  return;
}

