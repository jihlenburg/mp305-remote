/* Address: 0005b170; name: FUN_0005b170; body bytes: 114 */

undefined4 FUN_0005b170(int *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  
  if ((param_1[1] == 0) && (param_1[2] == 0)) {
    return 0;
  }
  uVar2 = 0;
  do {
    piVar1 = (int *)FUN_0004a118(&DAT_2003a4cc);
    while( true ) {
      if (piVar1 == (int *)0x0) {
        return uVar2;
      }
      if (((piVar1 != param_1) &&
          (((-1 < piVar1[0xd] || ((int)((uint)*(byte *)(piVar1 + 0x15) << 0x1c) < 0)) &&
           (*piVar1 == *param_1)))) && ((piVar1[1] != 0 && (piVar1[1] == param_1[1])))) break;
      piVar1 = (int *)FUN_0004a13c(&DAT_2003a4cc,piVar1);
    }
    FUN_0004a2ac(&DAT_2003a4cc,piVar1);
    if ((code *)piVar1[5] != (code *)0x0) {
      (*(code *)piVar1[5])(piVar1);
    }
    FUN_00046bec(piVar1);
    FUN_0002382c();
    uVar2 = 1;
  } while( true );
}

