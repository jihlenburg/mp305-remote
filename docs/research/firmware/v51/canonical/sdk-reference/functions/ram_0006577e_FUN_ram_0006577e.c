/* Address: ram:0006577e; name: FUN_ram_0006577e; body bytes: 38 */

undefined1 FUN_ram_0006577e(void)

{
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  auStack_11[0] = FUN_ram_00066ade();
  thunk_FUN_ram_000521a0(0x202e,1,auStack_11);
  return auStack_11[0];
}

