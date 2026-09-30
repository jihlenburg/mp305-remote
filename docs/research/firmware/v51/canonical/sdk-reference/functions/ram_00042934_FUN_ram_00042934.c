/* Address: ram:00042934; name: FUN_ram_00042934; body bytes: 32 */

int FUN_ram_00042934(int param_1,int param_2)

{
  uint uVar1;
  
  gp = 0x20004000;
  uVar1 = tmos_rand();
  return (int)((ulonglong)(uint)(param_2 - param_1) * (ulonglong)uVar1 >> 0x20) + param_1;
}

