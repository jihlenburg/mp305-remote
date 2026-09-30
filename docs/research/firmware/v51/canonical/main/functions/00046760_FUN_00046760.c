/* Address: 00046760; name: FUN_00046760; body bytes: 34 */

void FUN_00046760(int param_1)

{
  int *piVar1;
  
  for (piVar1 = DAT_2003a48c; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[5]) {
    if ((piVar1[1] == param_1) || (*piVar1 == param_1)) {
      *(byte *)(piVar1 + 6) = *(byte *)(piVar1 + 6) | 1;
    }
  }
  return;
}

