/* Address: ram:00065294; name: FUN_ram_00065294; body bytes: 36 */

undefined1 FUN_ram_00065294(void)

{
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  auStack_11[0] = LL_ClearWhiteList();
  thunk_FUN_ram_000521a0(0x2010,1,auStack_11);
  return auStack_11[0];
}

