/* Address: 000411a4; name: FUN_000411a4; body bytes: 32 */

undefined4 FUN_000411a4(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (DAT_2003a4f0 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000411c2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*DAT_2003a4f0)(param_1,param_2);
    return uVar1;
  }
  return 0;
}

