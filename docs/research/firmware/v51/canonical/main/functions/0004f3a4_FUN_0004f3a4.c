/* Address: 0004f3a4; name: FUN_0004f3a4; body bytes: 70 */

void FUN_0004f3a4(int *param_1)

{
  int *piVar1;
  int *piVar2;
  
  if (param_1 == (int *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  piVar1 = (int *)*param_1;
  while (piVar1 != (int *)0x0) {
    do {
      do {
        piVar2 = piVar1;
        piVar1 = (int *)piVar2[1];
      } while ((int *)piVar2[1] != (int *)0x0);
      piVar1 = (int *)piVar2[2];
    } while ((int *)piVar2[2] != (int *)0x0);
    piVar1 = (int *)*piVar2;
    if (piVar1 != (int *)0x0) {
      if ((int *)piVar1[1] == piVar2) {
        piVar1[1] = 0;
      }
      else {
        piVar1[2] = 0;
      }
    }
    FUN_00046bec(piVar2[4]);
    FUN_00046bec(piVar2);
  }
  *param_1 = 0;
  return;
}

