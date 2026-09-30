/* Address: ram:0006583e; name: FUN_ram_0006583e; body bytes: 38 */

undefined1 FUN_ram_0006583e(void)

{
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  auStack_11[0] = FUN_ram_00066eba();
  thunk_FUN_ram_000521a0(0x2037,1,auStack_11);
  return auStack_11[0];
}

