/* Address: 00041788; name: FUN_00041788; body bytes: 32 */

undefined4 FUN_00041788(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (DAT_2003a4fc != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000417a6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*DAT_2003a4fc)(param_1,param_2);
    return uVar1;
  }
  return 0;
}

