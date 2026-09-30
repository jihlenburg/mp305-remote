/* Address: ram:00050598; name: FUN_ram_00050598; body bytes: 56 */

void FUN_ram_00050598(undefined4 param_1,undefined1 param_2,undefined4 param_3)

{
  undefined1 local_50;
  undefined1 auStack_4f [71];
  
  gp = 0x20004000;
  local_50 = param_2;
  tmos_memcpy(auStack_4f,param_3,6);
  FUN_ram_0004e78a(param_1,8,&local_50,&LAB_ram_00050112);
  return;
}

