/* Address: ram:0004a878; name: FUN_ram_0004a878; body bytes: 30 */

void FUN_ram_0004a878(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  undefined2 auStack_12 [7];
  
  gp = 0x20004000;
  auStack_12[0] = param_3;
  FUN_ram_0004a6d0(param_1,param_2,auStack_12,2,0,0xfe);
  return;
}

