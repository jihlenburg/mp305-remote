/* Address: 00020dcc; name: FUN_00020dcc; body bytes: 8 */

/* Recovered from stored Thumb pointer at 0005055c; callback identification is inferred until
   reviewed. */

void FUN_00020dcc(undefined1 param_1,int param_2,uint param_3,uint param_4)

{
  if (param_3 < param_4) {
    *(undefined1 *)(param_2 + param_3) = param_1;
  }
  return;
}

