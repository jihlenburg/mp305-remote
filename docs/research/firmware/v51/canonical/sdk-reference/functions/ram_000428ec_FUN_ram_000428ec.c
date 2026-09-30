/* Address: ram:000428ec; name: FUN_ram_000428ec; body bytes: 36 */

uint FUN_ram_000428ec(int param_1,int param_2)

{
  uint uVar1;
  
  gp = 0x20004000;
  uVar1 = tmos_rand();
  return (int)((longlong)(param_2 - param_1) * (ulonglong)uVar1 >> 0x20) + param_1 & 0xff;
}

