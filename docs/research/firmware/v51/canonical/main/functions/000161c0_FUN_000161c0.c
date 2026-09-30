/* Address: 000161c0; name: FUN_000161c0; body bytes: 372 */

void FUN_000161c0(void)

{
  uint uVar1;
  undefined8 uVar2;
  longlong lVar3;
  undefined2 local_30;
  short local_2e;
  undefined4 local_2c;
  uint local_28 [3];
  undefined1 auStack_1c [8];
  
  FUN_00015174(0x20,1);
  FUN_000153b4(3,4,0x33);
  FUN_000153b4(2,0x1000,0x32);
  local_28[0] = 0;
  uVar1 = DAT_2003a60c >> ((DAT_40054020 & 0x7fff) >> 0xc);
  do {
    if (uVar1 / 0x18a4980 < (uint)(1 << (local_28[0] & 0xff))) break;
    local_28[0] = local_28[0] + 1;
  } while (local_28[0] < 8);
  FUN_0001683e(&DAT_4004e400);
  FUN_00016adc(local_28);
  local_28[1] = 380000;
  uVar2 = FUN_0001044c(1,0,local_28[0]);
  lVar3 = FUN_00010388(uVar1,0,(int)uVar2,(int)((ulonglong)uVar2 >> 0x20));
  local_28[2] = FUN_00010388((int)(lVar3 * 0xfa),(int)((ulonglong)(lVar3 * 0xfa) >> 0x20),1000000000
                             ,0);
  FUN_0001693c(&DAT_4004e400,local_28,auStack_1c);
  local_2e = 10;
  local_30 = 0x1b7;
  local_2c = 0x160cd;
  FUN_00016d4c(&local_30);
  FUN_00020076((int)local_2e);
  FUN_00020118((int)local_2e,0xf);
  FUN_000200c4((int)local_2e);
  local_2e = 0xb;
  local_30 = 0x1b4;
  local_2c = 0x16539;
  FUN_00016d4c(&local_30);
  FUN_00020076((int)local_2e);
  FUN_00020118((int)local_2e,0xf);
  FUN_000200c4((int)local_2e);
  local_2e = 0xd;
  local_30 = 0x1b6;
  local_2c = 0x165a9;
  FUN_00016d4c(&local_30);
  FUN_00020076((int)local_2e);
  FUN_00020118((int)local_2e,0xf);
  FUN_000200c4((int)local_2e);
  local_2e = 0xc;
  local_30 = 0x1b5;
  local_2c = 0x16651;
  FUN_00016d4c(&local_30);
  FUN_00020076((int)local_2e);
  FUN_00020118((int)local_2e,0xf);
  FUN_000200c4((int)local_2e);
  FUN_0001681c(&DAT_4004e400,1);
  DAT_1fff8f58 = 1;
  return;
}

