/* Address: 0003c2a4; name: FUN_0003c2a4; body bytes: 162 */

void FUN_0003c2a4(undefined4 param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = 0xffff;
  if (param_2 < 0x10000) {
    uVar1 = param_2 & 0xffff;
  }
  DAT_4001c018 = DAT_4001c018 & 0xfffff0ff | 0xc00;
  DAT_4005305c = DAT_4005305c & 0xfffffcff | 0x100;
  FUN_000153e0(1,0x10);
  DAT_1ffe015a = '\0';
  DAT_40053048 = DAT_40053048 & 0xffff | uVar1 << 0x10;
  DAT_40053040 = param_1;
  FUN_0001453c(&DAT_40053000,0,1);
  DAT_4001c004 = DAT_4001c004 | 0x40;
  while (DAT_1ffe015a == '\0') {
    thunk_FUN_000658d4(1);
  }
  FUN_000144fc();
  do {
  } while (-1 < DAT_4001c014 << 0x1a);
  DAT_4001c004 = DAT_4001c004 & 0xffffffbf;
  DAT_4001c018 = DAT_4001c018 & 0xfffff0ff | 0x400;
  DAT_4005305c = DAT_4005305c & 0xfffffcff;
  return;
}

