/* Address: 00046862; name: FUN_00046862; body bytes: 26 */

void FUN_00046862(int param_1,int param_2)

{
  int *piVar1;
  
  if (*(short *)(param_1 + 8) == 0x18) {
    piVar1 = (int *)FUN_0004673a();
    if (param_2 < *piVar1) {
      param_2 = *piVar1;
    }
    *piVar1 = param_2;
  }
  return;
}

