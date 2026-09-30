/* Address: ram:000525cc; name: thunk_FUN_ram_0006588a; body bytes: 4 */

undefined1 thunk_FUN_ram_0006588a(void)

{
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  auStack_11[0] = FUN_ram_00067198();
  thunk_FUN_ram_000521a0(0x2039,1,auStack_11);
  return auStack_11[0];
}

