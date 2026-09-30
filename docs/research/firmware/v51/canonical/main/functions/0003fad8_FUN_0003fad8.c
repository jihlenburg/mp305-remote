/* Address: 0003fad8; name: FUN_0003fad8; body bytes: 24 */

/* Recovered from stored Thumb pointer at 0007a6b8; callback identification is inferred until
   reviewed. */

void FUN_0003fad8(undefined4 param_1,int param_2)

{
  if ((*(byte *)(param_2 + 0x30) & 1) == 0) {
    FUN_00046bec(*(undefined4 *)(param_2 + 0x2c));
    *(undefined4 *)(param_2 + 0x2c) = 0;
  }
  return;
}

