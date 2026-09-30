/* Address: 00016bb8; name: FUN_00016bb8; body bytes: 76 */

/* Recovered from stored Thumb pointer at 000634f4; callback identification is inferred until
   reviewed. */

void FUN_00016bb8(void)

{
  undefined1 *puVar1;
  
  FUN_00016830(&DAT_4004e000,0x80);
  if (DAT_1fff8ebc <= DAT_1fff8eb0 - 1U) {
    puVar1 = (undefined1 *)(DAT_1fff8eac + DAT_1fff8ebc);
    DAT_1fff8ebc = DAT_1fff8ebc + 1;
    DAT_4004e024 = *puVar1;
    return;
  }
  FUN_00016988(&DAT_4004e000,0x80,0);
  FUN_00016988(&DAT_4004e000,8,1);
  return;
}

