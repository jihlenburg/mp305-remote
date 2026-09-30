/* Address: 0003f0e6; name: FUN_0003f0e6; body bytes: 74 */

int * FUN_0003f0e6(undefined4 *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)(*(code *)*param_1)();
  if (piVar1 != (int *)0x0) {
    piVar1[2] = param_3;
    piVar1[3] = 0;
    piVar1[4] = param_4;
    piVar1[5] = param_5;
    piVar1[6] = param_6;
    *piVar1 = (int)param_1;
    piVar1[1] = param_2;
    iVar2 = (*(code *)param_1[1])(piVar1);
    if (iVar2 == 0) {
      FUN_00046bec(piVar1);
      piVar1 = (int *)0x0;
    }
    else {
      FUN_0004aa40(piVar1 + 7);
    }
    return piVar1;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

