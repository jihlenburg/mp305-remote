/* Address: 00052708; name: FUN_00052708; body bytes: 26 */

undefined4 FUN_00052708(void)

{
  undefined4 uVar1;
  
  if (DAT_2003a4e0 == (code *)0x0) {
    DAT_2003a4dc = 1;
    return DAT_2003a4d8;
  }
                    /* WARNING: Could not recover jumptable at 0x00052712. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (*DAT_2003a4e0)();
  return uVar1;
}

