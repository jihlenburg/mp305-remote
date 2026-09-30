/* Address: 00047298; name: FUN_00047298; body bytes: 38 */

void FUN_00047298(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar1 = FUN_00036a1e(param_1,0x4a14b,0x4a145);
  if ((*(code **)(param_1 + 0x14) != (code *)0x0) && (iVar1 == 0)) {
                    /* WARNING: Could not recover jumptable at 0x000472b8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(param_1 + 0x14))(param_1,0);
    return;
  }
  return;
}

