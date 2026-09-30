/* Address: 00049a7c; name: FUN_00049a7c; body bytes: 50 */

void FUN_00049a7c(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = FUN_0004c924(param_1,0,0x16);
  uVar1 = uVar1 & 0xff;
  if ((uVar1 != 0) && (uVar1 <= DAT_2003a478)) {
                    /* WARNING: Could not recover jumptable at 0x00049aaa. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(DAT_2003a47c + uVar1 * 8))(param_1,*(undefined4 *)(DAT_2003a47c + uVar1 * 8 + 4));
    return;
  }
  return;
}

