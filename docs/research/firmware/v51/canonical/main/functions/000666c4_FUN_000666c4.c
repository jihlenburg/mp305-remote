/* Address: 000666c4; name: FUN_000666c4; body bytes: 70 */

int * FUN_000666c4(uint param_1,uint param_2)

{
  int *piVar1;
  
  piVar1 = (int *)0x0;
  if ((((param_1 != 0) && (param_2 <= 0xffffffff / param_1)) && (param_1 * param_2 < 0xffffffb8)) &&
     (piVar1 = (int *)FUN_00059f3c(param_1 * param_2 + 0x48), piVar1 != (int *)0x0)) {
    if (param_2 == 0) {
      *piVar1 = (int)piVar1;
    }
    else {
      *piVar1 = (int)(piVar1 + 0x12);
    }
    piVar1[0xf] = param_1;
    piVar1[0x10] = param_2;
    FUN_0006670c(piVar1,1);
  }
  return piVar1;
}

