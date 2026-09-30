/* Address: ram:0006522a; name: FUN_ram_0006522a; body bytes: 36 */

undefined1 FUN_ram_0006522a(void)

{
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  auStack_11[0] = FUN_ram_00065eb8();
  thunk_FUN_ram_000521a0(0x2005,1,auStack_11);
  return auStack_11[0];
}

