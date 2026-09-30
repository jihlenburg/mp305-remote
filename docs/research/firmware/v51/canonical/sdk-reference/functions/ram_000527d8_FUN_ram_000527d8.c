/* Address: ram:000527d8; name: FUN_ram_000527d8; body bytes: 470 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_000527d8(undefined1 param_1)

{
  gp = 0x20004000;
  DAT_ram_20001e7c = 0;
  tmos_memset(&DAT_ram_20001d60,0,0x118);
  LL_AdvertiseEventRegister(0);
  LL_ConnectEventRegister(0);
  DAT_ram_20001d74 = 0x7d7000c;
  DAT_ram_20001d78 = 0xc0ca180;
  DAT_ram_20001d7c = 0x7d7a180;
  DAT_ram_20001d80 = 0xa180;
  DAT_ram_20001e30 = 0x1f;
  DAT_ram_20001e34 = 0;
  DAT_ram_20001e20 = DAT_ram_20001e20 | 0x42d79ff;
  DAT_ram_20001e24 = DAT_ram_20001e24 | 0x9e;
  DAT_ram_20001e11 = DAT_ram_20001bca;
  DAT_ram_20001e19 = DAT_ram_20001bca;
  DAT_ram_20001e56 = 0xdfff;
  DAT_ram_20001e58 = 0xdfff;
  DAT_ram_20001e5a = 0x1f;
  _DAT_ram_20001d9a = 0xf0f;
  _DAT_ram_20001d9c = 0xf0f;
  DAT_ram_20001d99 = 0;
  DAT_ram_20001b67 = param_1;
  DAT_ram_20001e28 = DAT_ram_20001e20;
  DAT_ram_20001e2c = DAT_ram_20001e24;
  DAT_ram_20001d63 = FUN_ram_000428a6();
  DAT_ram_20001dd6 = 0x1cc;
  DAT_ram_20001d9f = 1;
  DAT_ram_20001da4 = 0;
  DAT_ram_20001de1 = (byte)((ushort)DAT_ram_20001bc0 >> 10);
  DAT_ram_20001da2 = 3;
  _DAT_ram_20001da8 = 0x6071440;
  DAT_ram_20001d8a = DAT_ram_20001bcc;
  if (0xfb < DAT_ram_20001bcc) {
    DAT_ram_20001d8a = 0xfb;
  }
  if ((_DAT_ram_20001d9c & 4) == 0) {
    DAT_ram_20001d8c = (undefined *)((DAT_ram_20001d8a + 0xe) * 8);
  }
  else {
    DAT_ram_20001d8c = (undefined *)((short)&pmpaddr32 + DAT_ram_20001d8a * 0x40);
  }
  if ((_DAT_ram_20001d9c & 0x400) == 0) {
    DAT_ram_20001d90 = (undefined *)((DAT_ram_20001d8a + 0xe) * 8);
  }
  else {
    DAT_ram_20001d90 = (undefined *)((short)&pmpaddr32 + DAT_ram_20001d8a * 0x40);
  }
  DAT_ram_20001d82 = DAT_ram_20001d8a;
  if (DAT_ram_20001d8a < 0x1b) {
    DAT_ram_20001d82 = 0x1b;
  }
  DAT_ram_20001d84 = DAT_ram_20001d8c;
  if (DAT_ram_20001d8c < 0x148) {
    DAT_ram_20001d84 = (undefined *)0x148;
  }
  DAT_ram_20001d86 = DAT_ram_20001d84;
  if (0x848 < DAT_ram_20001d84) {
    DAT_ram_20001d86 = (undefined *)0x848;
  }
  DAT_ram_20001da0 = 0x1cc;
  DAT_ram_20001d94 = 0x15f900;
  DAT_ram_20001d88 = DAT_ram_20001d84;
  DAT_ram_20001d8e = DAT_ram_20001d8a;
  FUN_ram_000626ac();
  FUN_ram_00057e02();
  FUN_ram_0006194a();
  FUN_ram_0005d99a();
  return;
}

