/* Address: 000461d4; name: FUN_000461d4; body bytes: 10 */

undefined * FUN_000461d4(int param_1)

{
  undefined *puVar1;
  
  puVar1 = *(undefined **)(param_1 + 0x38);
  if (puVar1 == (undefined *)0x0) {
    puVar1 = &DAT_000461e0;
  }
  return puVar1;
}

