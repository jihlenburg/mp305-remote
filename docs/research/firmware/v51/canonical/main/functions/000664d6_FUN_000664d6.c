/* Address: 000664d6; name: FUN_000664d6; body bytes: 26 */

undefined4 * FUN_000664d6(void)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_00059f3c(0x18);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = 0;
    FUN_000656b6(puVar1 + 1);
  }
  return puVar1;
}

