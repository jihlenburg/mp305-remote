/* Address: 00066608; name: FUN_00066608; body bytes: 132 */

undefined4 FUN_00066608(void)

{
  uint uVar1;
  undefined1 local_10;
  
  DAT_1ffe0054 = 0x50;
  uVar1 = 7;
  for (local_10 = 0xff; (int)((uint)local_10 << 0x18) < 0; local_10 = local_10 << 1) {
    uVar1 = uVar1 - 1;
  }
  DAT_1ffe005c = (uVar1 & 7) << 8;
  DAT_e000ed20 = DAT_e000ed20 | 0xf0f00000;
  FUN_0006579c();
  DAT_1ffe0058 = 0;
  FUN_000102e0();
  DAT_e000ef34 = DAT_e000ef34 | 0xc0000000;
  FUN_000102b8();
  return 0;
}

