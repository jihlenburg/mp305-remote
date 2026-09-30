/* Address: ram:00050212; name: FUN_ram_00050212; body bytes: 48 */

undefined4 FUN_ram_00050212(undefined2 *param_1)

{
  undefined4 uVar1;
  undefined1 auStack_50 [72];
  
  gp = 0x20004000;
  if (param_1 != (undefined2 *)0x0) {
    FUN_ram_0004e85c(param_1,auStack_50);
    uVar1 = FUN_ram_0004e78a(*param_1,7,auStack_50,FUN_ram_0004fffa);
    return uVar1;
  }
  return 1;
}

