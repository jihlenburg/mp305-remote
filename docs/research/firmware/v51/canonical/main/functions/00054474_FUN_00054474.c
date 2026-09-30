/* Address: 00054474; name: FUN_00054474; body bytes: 470 */

void FUN_00054474(uint param_1)

{
  int iVar1;
  
  if (current_mode == param_1) {
    return;
  }
  FUN_0001814c();
  FUN_00052a74(DAT_1ffe02a4);
  FUN_00052a74(DAT_1ffe02a8);
  if (DAT_1ffe0330 == DAT_1ffe0468) {
    FUN_0004e5a6(DAT_1ffe0474,7,0);
  }
  if ((DAT_1ffe04f4 != 0) && (iVar1 = FUN_000527ec(DAT_1ffe0504), iVar1 == DAT_1ffe0534)) {
    FUN_000527f0(DAT_1ffe0504,DAT_1ffe0508,0);
  }
  iVar1 = FUN_000527ec(DAT_1ffe0344);
  if (iVar1 == DAT_1ffe04f0) {
    FUN_000527f0(DAT_1ffe0344,DAT_1ffe0348,0);
  }
  if (param_1 == 0) {
    iVar1 = DAT_1ffe04f4;
    if ((current_mode != 1) && (iVar1 = DAT_1ffe05b8, current_mode != 2)) {
      iVar1 = DAT_1ffe0620;
    }
    FUN_0004b3a0(iVar1);
    DAT_1ffe04f4 = 0;
    DAT_1ffe05b8 = 0;
    DAT_1ffe0620 = 0;
    if (DAT_1ffe034c == 0) {
      FUN_000301e8();
    }
    set_voltage_raw(DAT_1fffab74);
    set_current_raw(DAT_1fffab76);
    FUN_0004aa6e(DAT_1ffe0344,0x10);
  }
  else {
    if (param_1 == 1) {
      iVar1 = DAT_1ffe034c;
      if ((current_mode != 0) && (iVar1 = DAT_1ffe05b8, current_mode != 2)) {
        iVar1 = DAT_1ffe0620;
      }
      FUN_0004b3a0(iVar1);
      DAT_1ffe034c = 0;
      DAT_1ffe05b8 = 0;
      DAT_1ffe0620 = 0;
      DAT_1fffab48 = 0;
      if (DAT_1ffe04f4 == 0) {
        FUN_0002f6e4();
      }
      FUN_0004e00e(DAT_1ffe0344,0x10);
      FUN_00017cf8();
      goto LAB_0005461c;
    }
    if (param_1 == 2) {
      iVar1 = DAT_1ffe034c;
      if ((current_mode != 0) && (iVar1 = DAT_1ffe04f4, current_mode != 1)) {
        iVar1 = DAT_1ffe0620;
      }
      FUN_0004b3a0(iVar1);
      DAT_1ffe034c = 0;
      DAT_1ffe04f4 = 0;
      DAT_1ffe0620 = 0;
      if (DAT_1ffe05b8 == 0) {
        FUN_00033538();
      }
    }
    else {
      if (param_1 != 3) goto LAB_0005461c;
      iVar1 = DAT_1ffe034c;
      if ((current_mode != 0) && (iVar1 = DAT_1ffe04f4, current_mode != 1)) {
        iVar1 = DAT_1ffe05b8;
      }
      FUN_0004b3a0(iVar1);
      DAT_1ffe034c = 0;
      DAT_1ffe04f4 = 0;
      DAT_1ffe05b8 = 0;
      if (DAT_1ffe0620 == 0) {
        FUN_0002aa74();
      }
    }
    FUN_0004e00e(DAT_1ffe0344,0x10);
  }
  FUN_00018114(DAT_1ffe0348);
LAB_0005461c:
  current_mode = (byte)param_1;
  FUN_0001a5fc();
  FUN_0001af48(param_1);
  FUN_00057ea0(DAT_1fffaace,1);
  FUN_00052aae(DAT_1ffe02a4);
  FUN_00052aae(DAT_1ffe02a8);
  return;
}

