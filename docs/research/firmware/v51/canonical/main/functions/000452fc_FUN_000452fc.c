/* Address: 000452fc; name: FUN_000452fc; body bytes: 46 */

void FUN_000452fc(void)

{
  uint uVar1;
  
  uVar1 = 0;
  do {
    if ((&DAT_2003a55c)[uVar1 * 7] != 0) {
      FUN_00046bec();
    }
    FUN_0004a602(&DAT_2003a55c + uVar1 * 7,0x1c);
    uVar1 = uVar1 + 1 & 0xff;
  } while (uVar1 < 4);
  return;
}

