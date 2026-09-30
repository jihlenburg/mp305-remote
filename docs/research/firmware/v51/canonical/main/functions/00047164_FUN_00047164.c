/* Address: 00047164; name: FUN_00047164; body bytes: 64 */

void FUN_00047164(int param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  
  if (param_1 != 0) {
    FUN_0004737c(param_2);
    if (*(int *)(param_2 + 8) == 0) {
      FUN_0004af28(param_2);
    }
    *(int *)(*(int *)(param_2 + 8) + 4) = param_1;
    piVar1 = (int *)FUN_0004a200(param_1);
    if (piVar1 == (int *)0x0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    *piVar1 = param_2;
    piVar2 = (int *)FUN_0004a118(param_1);
    if (piVar2 == piVar1) {
      FUN_00047304(param_1);
      return;
    }
  }
  return;
}

