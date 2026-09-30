/* Address: 000657f0; name: FUN_000657f0; body bytes: 54 */

void FUN_000657f0(int param_1,int param_2)

{
  int *piVar1;
  uint uVar2;
  
  piVar1 = (int *)0x0;
  if (param_2 != 0) {
    uVar2 = 0;
    do {
      if ((&DAT_1ffe0d60)[uVar2 * 2] == param_1) {
        piVar1 = &DAT_1ffe0d5c + uVar2 * 2;
        break;
      }
      if ((piVar1 == (int *)0x0) && ((&DAT_1ffe0d5c)[uVar2 * 2] == 0)) {
        piVar1 = &DAT_1ffe0d5c + uVar2 * 2;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < 8);
    if (piVar1 != (int *)0x0) {
      *piVar1 = param_2;
      piVar1[1] = param_1;
    }
  }
  return;
}

