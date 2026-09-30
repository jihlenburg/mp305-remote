/* Address: 0001920c; name: FUN_0001920c; body bytes: 236 */

void FUN_0001920c(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  
  if ((DAT_1fffaae5 == 2) || (DAT_1fffaae5 == 3)) {
    iVar2 = FUN_0001919c(param_1,500);
    DAT_1fffaae7 = (char)iVar2;
    if (iVar2 == 100) {
      FUN_0001afe0(1);
      DAT_1fffaae1 = 0;
      DAT_1fffab1c = 1;
      DAT_1fff9550 = DAT_1fff9550 | 1;
    }
    if (DAT_1fffaae5 == 2) {
      DAT_1fffabb0 = DAT_1fffabb0 + param_1;
      if (DAT_1fffaae7 == '\0') {
        if (2999 < DAT_1fffabb0) {
          uVar1 = 1;
          goto LAB_000192d4;
        }
      }
      else {
        DAT_1fffabb0 = 0;
      }
    }
    else if ((DAT_1fffaae5 == 3) && (DAT_1fffaae7 != '\0')) {
      DAT_1fffab90 = 0;
    }
  }
  else if (DAT_1fffaae5 == 1) {
    iVar2 = FUN_0001919c(param_1,500);
    if ((iVar2 != 0) && (iVar2 = FUN_0001a2cc(), iVar2 < 1)) {
      uVar1 = 2;
LAB_000192d4:
      enter_critical();
      DAT_1fffaa54 = uVar1;
      exit_critical();
      return;
    }
  }
  else if (3 < DAT_1fffaae5) {
    iVar2 = FUN_0001919c(param_1,1000);
    DAT_1fffaae7 = (char)iVar2;
    if (iVar2 == 0xff) {
      DAT_1fffaae0 = 1;
      DAT_1fffaae1 = 0;
    }
    else if (iVar2 == 100) {
      FUN_0001afb4(1);
      DAT_1fffaae1 = 1;
      remote_granted = 0;
      DAT_1fffab1c = 0;
      DAT_1fffaacf = 0;
      DAT_1fff9550 = DAT_1fff9550 | 1;
    }
  }
  return;
}

