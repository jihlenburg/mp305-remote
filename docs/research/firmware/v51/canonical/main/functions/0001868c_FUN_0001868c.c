/* Address: 0001868c; name: FUN_0001868c; body bytes: 92 */

undefined4 FUN_0001868c(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = FUN_000186f0();
  if (iVar1 == 0) {
    if ((DAT_1fffab1b != '\0') && (0x13 < DAT_1ffe017c)) {
      DAT_1fffab88 = 0;
      DAT_1fffab8c = 0;
      DAT_1fffab90 = 0;
    }
    DAT_1ffe017c = 0;
  }
  else {
    DAT_1ffe017c = DAT_1ffe017c + param_1;
    if (DAT_1ffe017c == 0x32) {
      uVar2 = 1;
    }
  }
  if (DAT_1fffaae9 != '\0') {
    DAT_1fffaae9 = '\0';
    uVar2 = 1;
  }
  if ((DAT_1fffab17 == '\x01') ||
     ((DAT_1fffaad3 != '\0' && (iVar1 = get_output_enabled(), iVar1 == 0)))) {
    uVar2 = 0;
  }
  return uVar2;
}

