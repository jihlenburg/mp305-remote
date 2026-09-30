/* Address: ram:0005ce04; name: FUN_ram_0005ce04; body bytes: 20 */

int FUN_ram_0005ce04(void)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  return (uint)(iVar1 == 0) << 1;
}

