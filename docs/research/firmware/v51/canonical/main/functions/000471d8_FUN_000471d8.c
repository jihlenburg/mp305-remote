/* Address: 000471d8; name: FUN_000471d8; body bytes: 38 */

void FUN_000471d8(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  iVar1 = FUN_00036a1e(param_1,0x4a119,0x4a13d);
  if ((*(code **)(param_1 + 0x14) != (code *)0x0) && (iVar1 == 0)) {
                    /* WARNING: Could not recover jumptable at 0x000471f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(param_1 + 0x14))(param_1,1);
    return;
  }
  return;
}

