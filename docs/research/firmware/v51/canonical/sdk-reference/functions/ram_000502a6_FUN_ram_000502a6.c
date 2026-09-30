/* Address: ram:000502a6; name: FUN_ram_000502a6; body bytes: 52 */

void FUN_ram_000502a6(undefined2 *param_1)

{
  undefined1 auStack_50 [72];
  
  gp = 0x20004000;
  tmos_memcpy(auStack_50,param_1 + 0x1e,0x10);
  FUN_ram_0004e78a(*param_1,0x11,auStack_50,&LAB_ram_0005003e);
  return;
}

