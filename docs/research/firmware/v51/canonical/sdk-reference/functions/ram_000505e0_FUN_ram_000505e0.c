/* Address: ram:000505e0; name: FUN_ram_000505e0; body bytes: 56 */

void FUN_ram_000505e0(undefined4 param_1,undefined2 param_2,undefined4 param_3)

{
  undefined2 local_50;
  undefined1 auStack_4e [70];
  
  gp = 0x20004000;
  local_50 = param_2;
  tmos_memcpy(auStack_4e,param_3,8);
  FUN_ram_0004e78a(param_1,0xb,&local_50,&LAB_ram_0005009e);
  return;
}

