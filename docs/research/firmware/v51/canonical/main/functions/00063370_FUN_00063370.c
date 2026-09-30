/* Address: 00063370; name: FUN_00063370; body bytes: 352 */

void FUN_00063370(void)

{
  int iVar1;
  uint uVar2;
  undefined8 uVar3;
  longlong lVar4;
  undefined2 local_30;
  short local_2e;
  undefined4 local_2c;
  uint local_28 [3];
  undefined1 auStack_1c [8];
  
  FUN_00015174(0x10,1);
  local_28[0] = 0;
  uVar2 = DAT_2003a60c >> ((DAT_40054020 & 0x7fff) >> 0xc);
  do {
    if (uVar2 / 13600000 < (uint)(1 << (local_28[0] & 0xff))) break;
    local_28[0] = local_28[0] + 1;
  } while (local_28[0] < 8);
  FUN_0001683e(&DAT_4004e000);
  FUN_00016adc(local_28);
  local_28[1] = 200000;
  uVar3 = FUN_0001044c(1,0,local_28[0]);
  lVar4 = FUN_00010388(uVar2,0,(int)uVar3,(int)((ulonglong)uVar3 >> 0x20));
  local_28[2] = FUN_00010388((int)(lVar4 * 0xfa),(int)((ulonglong)(lVar4 * 0xfa) >> 0x20),1000000000
                             ,0);
  iVar1 = FUN_0001693c(&DAT_4004e000,local_28,auStack_1c);
  if (iVar1 == 0) {
    local_2e = 0x19;
    local_30 = 0x1b3;
    local_2c = 0x16855;
    FUN_00016d4c(&local_30);
    FUN_0002005c((int)local_2e);
    FUN_000200f8((int)local_2e,0xf);
    FUN_000200aa((int)local_2e);
    local_2e = 0x1a;
    local_30 = 0x1b0;
    local_2c = 0x169f1;
    FUN_00016d4c(&local_30);
    FUN_0002005c((int)local_2e);
    FUN_000200f8((int)local_2e,0xf);
    FUN_000200aa((int)local_2e);
    local_2e = 0x1b;
    local_30 = 0x1b2;
    local_2c = 0x16af9;
    FUN_00016d4c(&local_30);
    FUN_0002005c((int)local_2e);
    FUN_000200f8((int)local_2e,0xf);
    FUN_000200aa((int)local_2e);
    local_2e = 0x1c;
    local_30 = 0x1b1;
    local_2c = 0x16bb9;
    FUN_00016d4c(&local_30);
    FUN_0002005c((int)local_2e);
    FUN_000200f8((int)local_2e,0xf);
    FUN_000200aa((int)local_2e);
    FUN_0001681c(&DAT_4004e000,1);
  }
  DAT_1fff8ec0 = 1;
  return;
}

