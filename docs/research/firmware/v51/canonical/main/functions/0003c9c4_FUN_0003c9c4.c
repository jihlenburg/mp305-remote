/* Address: 0003c9c4; name: FUN_0003c9c4; body bytes: 46 */

void FUN_0003c9c4(int param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_0004a118();
  while ((piVar1 != (int *)0x0 &&
         ((*piVar1 != param_1 || ((piVar1[1] != param_2 && (param_2 != 0))))))) {
    piVar1 = (int *)FUN_0004a13c(&DAT_2003a4cc,piVar1);
  }
  return;
}

