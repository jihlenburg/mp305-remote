/* Address: ram:0004f5a8; name: FUN_ram_0004f5a8; body bytes: 42 */

void FUN_ram_0004f5a8(undefined4 param_1)

{
  gp = 0x20004000;
  FUN_ram_0004f4fe();
  DAT_ram_20001d4f = (undefined1)param_1;
  FUN_ram_0004c80e(param_1,6);
  linkDB_Register(FUN_ram_0004e602);
  return;
}

