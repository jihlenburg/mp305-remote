/* Address: ram:000652b8; name: FUN_ram_000652b8; body bytes: 36 */

undefined1 FUN_ram_000652b8(void)

{
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  auStack_11[0] = LL_AddWhiteListDevice();
  thunk_FUN_ram_000521a0(0x2011,1,auStack_11);
  return auStack_11[0];
}

