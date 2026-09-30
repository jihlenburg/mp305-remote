/* Address: 0003a670; name: FUN_0003a670; body bytes: 48 */

/* Recovered from stored Thumb pointer at 0003a314; callback identification is inferred until
   reviewed. */

void FUN_0003a670(int param_1)

{
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_000485a4();
  if ((((*(byte *)(param_1 + 0x98) & 0xf) == 0) || (*(int *)(param_1 + 0x70) == 0)) &&
     (*(int *)(param_1 + 0xc0) != 0)) {
    FUN_0003c97c(param_1,0x3a671);
    return;
  }
  return;
}

