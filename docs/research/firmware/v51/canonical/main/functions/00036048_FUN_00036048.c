/* Address: 00036048; name: FUN_00036048; body bytes: 58 */

void FUN_00036048(void)

{
  if (DAT_1fffab1d != '\0') {
    FUN_00052a74(DAT_1ffe02a4);
    FUN_00052a74(DAT_1ffe02a8);
    DAT_1fffab1d = '\0';
    DAT_1fffab1e = 1;
    DAT_1fffab20 = 0;
    FUN_0001cd54(0);
    FUN_000151bc();
    FUN_0001ca60(200);
    DAT_1fffab1f = 0;
  }
  return;
}

