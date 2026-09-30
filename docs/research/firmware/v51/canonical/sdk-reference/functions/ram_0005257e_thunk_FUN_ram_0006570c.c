/* Address: ram:0005257e; name: thunk_FUN_ram_0006570c; body bytes: 4 */

undefined1 thunk_FUN_ram_0006570c(void)

{
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  auStack_11[0] = FUN_ram_00066994();
  thunk_FUN_ram_000521a0(0x2027,1,auStack_11);
  return auStack_11[0];
}

