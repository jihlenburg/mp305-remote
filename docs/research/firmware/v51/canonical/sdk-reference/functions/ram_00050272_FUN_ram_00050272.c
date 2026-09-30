/* Address: ram:00050272; name: FUN_ram_00050272; body bytes: 52 */

void FUN_ram_00050272(undefined2 *param_1)

{
  undefined1 auStack_50 [72];
  
  gp = 0x20004000;
  tmos_memcpy(auStack_50,param_1 + 0x16,0x10);
  FUN_ram_0004e78a(*param_1,0x11,auStack_50,&LAB_ram_0005000e);
  return;
}

