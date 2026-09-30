/* Address: ram:000652fa; name: FUN_ram_000652fa; body bytes: 36 */

undefined1 FUN_ram_000652fa(void)

{
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  auStack_11[0] = FUN_ram_0006656c();
  thunk_FUN_ram_000521a0(0x2014,1,auStack_11);
  return auStack_11[0];
}

