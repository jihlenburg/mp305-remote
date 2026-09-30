/* Address: ram:0005251e; name: thunk_FUN_ram_0006517c; body bytes: 4 */

undefined1 thunk_FUN_ram_0006517c(undefined1 param_1)

{
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  auStack_11[0] = 0;
  DAT_ram_20001dac = param_1;
  thunk_FUN_ram_000521a0(0xc49,1,auStack_11);
  return auStack_11[0];
}

