/* Address: 0003cabc; name: FUN_0003cabc; body bytes: 16 */

/* Recovered from stored Thumb pointer at 000246c0; callback identification is inferred until
   reviewed. */

undefined4 FUN_0003cabc(int param_1)

{
  if (*(int *)(param_1 + 0x30) <= *(int *)(param_1 + 0x34)) {
    return *(undefined4 *)(param_1 + 0x2c);
  }
  return *(undefined4 *)(param_1 + 0x24);
}

