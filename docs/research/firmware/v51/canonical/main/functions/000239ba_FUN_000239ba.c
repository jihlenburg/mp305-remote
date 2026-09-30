/* Address: 000239ba; name: FUN_000239ba; body bytes: 12 */

/* Recovered from stored Thumb pointer at 00050a00; callback identification is inferred until
   reviewed. */

void FUN_000239ba(undefined4 param_1,undefined4 param_2)

{
  uint in_fpscr;
  undefined4 uVar1;
  
  uVar1 = VectorUnsignedToFloat(param_2,(byte)(in_fpscr >> 0x16) & 3);
  FUN_0003d614(uVar1);
  return;
}

