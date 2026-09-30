/* Address: 00036bb0; name: FUN_00036bb0; body bytes: 498 */

void FUN_00036bb0(void)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  
  DAT_1fffaace = 0;
  DAT_1fffaad1 = 0;
  DAT_1fffaad8 = 0;
  DAT_1fffab0a = 0;
  DAT_1fffab74 = DAT_1fffa0d4;
  DAT_1fffab76 = DAT_1fffa0d6;
  DAT_1fffab78 = 0;
  DAT_1fffab7a = 0;
  DAT_1fffab7c = 0;
  DAT_1fffab48 = 0;
  DAT_1fffaae2 = 0;
  DAT_1fffaae3 = 0;
  DAT_1fffaacd = 0;
  DAT_1fffaadd = 0;
  remote_granted = 0;
  DAT_1fffaaec = 1;
  DAT_1fffab06 = (undefined1)((DAT_1fffa0d0 + 5) / 10);
  DAT_1fffaadc = DAT_1fffa0c6;
  DAT_1fffaadb = DAT_1fffa0c5;
  DAT_1fffaade = DAT_1fffa0c4;
  DAT_1fffaae4 = DAT_1fffa0c3;
  current_mode = DAT_1fffa0bf;
  requested_mode = DAT_1fffa0bf;
  DAT_1fffab03 = DAT_1fffa0c1;
  DAT_1fffab04 = DAT_1fffa0c2;
  DAT_1fffab4a = (undefined2)(DAT_1fffa124 / 1000);
  DAT_1fffaaf9 = DAT_1fffa0ba;
  DAT_1fffaafe = DAT_1fffa0bc;
  DAT_1fffaafa = DAT_1fffa0bd;
  DAT_1fffaaff = DAT_1fffa0be;
  DAT_1fffaafb = DAT_1fffa0bb;
  DAT_1fffab62 = DAT_1fffa0d8;
  DAT_1fffab64 = DAT_1fffa0da;
  DAT_1fffab70 = DAT_1fffa0f4;
  DAT_1fffab88 = 0;
  DAT_1fffab8c = 0;
  DAT_1fffabbc = 0;
  DAT_1fffaaf7 = 0xff;
  uVar3 = (uint)DAT_1fffa0c7;
  DAT_1fffac94._2_1_ = DAT_1fffa0c7;
  DAT_1fffac94._0_2_ = *(ushort *)((int)&DAT_1fffa0dc + uVar3 * 2);
  DAT_1fffac90._2_2_ = (&DAT_1fffa0e8)[uVar3];
  DAT_1fffac90._0_1_ = (&DAT_1fffa0c8)[uVar3];
  DAT_1fffab60 = 200;
  uVar2 = 0;
  do {
    if (DAT_1fffa0ba <= (byte)(&DAT_1ffe0778)[uVar2]) {
      DAT_1ffe032c = (undefined1)uVar2;
      break;
    }
    uVar2 = uVar2 + 1 & 0xff;
  } while (uVar2 < 5);
  uVar2 = 0;
  do {
    if (DAT_1fffa0be <= (byte)(&DAT_1ffe077d)[uVar2]) {
      DAT_1ffe0864 = (undefined1)uVar2;
      break;
    }
    uVar2 = uVar2 + 1 & 0xff;
  } while (uVar2 < 6);
  uVar2 = 0;
  do {
    if (DAT_1fffa0d8 <= (ushort)(&DAT_1ffe0784)[uVar2]) {
      DAT_1ffe0865 = (undefined1)uVar2;
      break;
    }
    uVar2 = uVar2 + 1 & 0xff;
  } while (uVar2 < 10);
  uVar2 = 0;
  do {
    if (DAT_1fffa0da <= (ushort)(&DAT_1ffe0798)[uVar2]) {
      DAT_1ffe0867 = (undefined1)uVar2;
      break;
    }
    uVar2 = uVar2 + 1 & 0xff;
  } while (uVar2 < 6);
  uVar2 = 0;
  do {
    if (DAT_1fffa0f4 <= (ushort)(&DAT_1ffe07a4)[uVar2]) {
      DAT_1ffe0866 = (undefined1)uVar2;
      break;
    }
    uVar2 = uVar2 + 1 & 0xff;
  } while (uVar2 < 0xb);
  uVar2 = 0;
  do {
    if ((ushort)DAT_1fffac94 <= (ushort)(&DAT_1ffe07e0)[uVar3 * 0xb + uVar2]) {
      DAT_1ffe032d = (undefined1)uVar2;
      break;
    }
    uVar2 = uVar2 + 1 & 0xff;
  } while (uVar2 < 0xb);
  uVar1 = 0;
  do {
    if (DAT_1fffac90._2_2_ <= (ushort)((uVar1 + 1) * 100)) {
      DAT_1ffe032e = (undefined1)uVar1;
      break;
    }
    uVar1 = uVar1 + 1 & 0xff;
  } while (uVar1 < 0x32);
  set_voltage_raw(DAT_1fffa0d4);
  set_current_raw(DAT_1fffab76);
  DAT_1fffab1f = 1;
  return;
}

