/* Address: 0004dfd2; name: FUN_0004dfd2; body bytes: 60 */

undefined4 FUN_0004dfd2(int param_1,int param_2)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  uVar1 = FUN_0004bb8c();
  uVar3 = 0;
  while( true ) {
    if (uVar1 <= uVar3) {
      return 0;
    }
    piVar2 = (int *)FUN_0004bb9e(param_1,uVar3);
    if (*piVar2 == param_2) break;
    uVar3 = uVar3 + 1;
  }
  FUN_0004dfc0(param_1,uVar3);
  return 1;
}

