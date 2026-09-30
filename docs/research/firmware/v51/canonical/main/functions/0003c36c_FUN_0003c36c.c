/* Address: 0003c36c; name: FUN_0003c36c; body bytes: 222 */

void FUN_0003c36c(void)

{
  undefined4 extraout_r1;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 local_18;
  undefined4 local_10;
  uint local_c;
  
  FUN_0003c170();
  FUN_00015174(0x10000);
  FUN_0001bd0c(&DAT_4001c000);
  FUN_0001c06c(&local_38);
  local_38 = 0;
  local_34 = 0;
  uStack_30 = 8;
  local_20 = 0;
  uStack_1c = 0x400;
  local_24 = 0;
  local_28 = 0;
  local_18 = 0;
  local_10 = 0;
  FUN_0001bfde(&DAT_4001c000,&local_38);
  FUN_0003c068();
  FUN_00015384(1,8);
  thunk_FUN_000658d4(100);
  FUN_000153e0(1,8);
  thunk_FUN_000658d4(0x32);
  FUN_00060258();
  DAT_1fff8ed6 = 0x2a;
  DAT_1fff8ed8 = 0x2b;
  DAT_1fff8ed4 = 0x2c;
  if (DAT_1fffa0bb == '\0') {
    DAT_1fff8ecc = 0xf0;
    DAT_1fff8ece = 0x140;
    local_c = 0;
    DAT_1fff8ed2 = 0;
  }
  else if (DAT_1fffa0bb == '\x01') {
    DAT_1fff8ecc = 0x140;
    DAT_1fff8ece = 0xf0;
    DAT_1fff8ed2 = 1;
    local_c = 0x60;
  }
  else if (DAT_1fffa0bb == '\x02') {
    DAT_1fff8ecc = 0xf0;
    DAT_1fff8ece = 0x140;
    DAT_1fff8ed2 = 2;
    local_c = 0xc0;
  }
  else {
    if (DAT_1fffa0bb != '\x03') {
      return;
    }
    DAT_1fff8ecc = 0x140;
    DAT_1fff8ece = 0xf0;
    DAT_1fff8ed2 = 3;
    local_c = 0xa0;
  }
  local_10 = 0x36;
  FUN_0003c132(0x36);
  FUN_0003c150(local_c & 0xff,extraout_r1,local_10,local_c);
  return;
}

