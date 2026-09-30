/* Address: 0001d958; name: FUN_0001d958; body bytes: 148 */

void FUN_0001d958(void)

{
  int iVar1;
  
  enter_critical();
  DAT_1fffa0d0 = DAT_1fffa9d8;
  DAT_1fffa120 = DAT_1fffa994;
  DAT_1fffa0d4 = DAT_1fffab74;
  DAT_1fffa0d6 = DAT_1fffab76;
  DAT_1fffa0c1 = DAT_1fffab03;
  DAT_1fffa0c2 = DAT_1fffab04;
  DAT_1fffa0bf = current_mode;
  DAT_1fffa0c3 = DAT_1fffaae4;
  DAT_1fffa0c4 = DAT_1fffaade;
  DAT_1fffa0c5 = DAT_1fffaadb;
  DAT_1fffa0c6 = DAT_1fffaadc;
  DAT_1fffa0ba = DAT_1fffaaf9;
  DAT_1fffa0bc = DAT_1fffaafe;
  DAT_1fffa0bd = DAT_1fffaafa;
  DAT_1fffa0be = DAT_1fffaaff;
  DAT_1fffa0bb = DAT_1fffaafb;
  DAT_1fffa0d8 = DAT_1fffab62;
  DAT_1fffa0da = DAT_1fffab64;
  DAT_1fffa0f4 = DAT_1fffab70;
  iVar1 = FUN_00015f5c();
  if (iVar1 != DAT_1fffa134) {
    DAT_1fffa0b8 = DAT_1fffa0b8 + '\x01';
    FUN_0001c364();
  }
  DAT_1fffa8cd = 1;
  exit_critical();
  return;
}

