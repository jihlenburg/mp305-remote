/* Address: 00052a58; name: FUN_00052a58; body bytes: 24 */

void FUN_00052a58(void)

{
  DAT_2003a4a4 = 0;
  if (DAT_2003a4bc != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00052a6c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*DAT_2003a4bc)(DAT_2003a4c0);
    return;
  }
  return;
}

