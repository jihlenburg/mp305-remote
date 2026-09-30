/* Address: 0003c97c; name: FUN_0003c97c; body bytes: 68 */

undefined4 FUN_0003c97c(int param_1,int param_2)

{
  int *piVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  do {
    piVar1 = (int *)FUN_0004a118(&DAT_2003a4cc);
    while( true ) {
      if (piVar1 == (int *)0x0) {
        return uVar2;
      }
      if (((*piVar1 == param_1) || (param_1 == 0)) && ((piVar1[1] == param_2 || (param_2 == 0))))
      break;
      piVar1 = (int *)FUN_0004a13c(&DAT_2003a4cc,piVar1);
    }
    FUN_0005b0f4();
    FUN_0002382c();
    uVar2 = 1;
  } while( true );
}

