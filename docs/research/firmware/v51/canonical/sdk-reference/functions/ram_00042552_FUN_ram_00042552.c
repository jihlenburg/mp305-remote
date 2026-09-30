/* Address: ram:00042552; name: FUN_ram_00042552; body bytes: 30 */

undefined4 FUN_ram_00042552(code *param_1)

{
  gp = 0x20004000;
  DAT_ram_20001bfc = param_1;
  DAT_ram_20001b7c = (*param_1)();
  return 0;
}

