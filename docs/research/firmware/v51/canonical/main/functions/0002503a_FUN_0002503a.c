/* Address: 0002503a; name: FUN_0002503a; body bytes: 12 */

/* Recovered from stored Thumb pointer at 000415f8; callback identification is inferred until
   reviewed. */

uint FUN_0002503a(int param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = param_1 + 3U & 0xfffffffc;
  }
  return uVar1;
}

