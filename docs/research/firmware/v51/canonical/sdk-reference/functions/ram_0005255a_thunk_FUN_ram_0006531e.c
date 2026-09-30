/* Address: ram:0005255a; name: thunk_FUN_ram_0006531e; body bytes: 4 */

undefined4 thunk_FUN_ram_0006531e(void)

{
  undefined1 uStack_1c;
  undefined1 auStack_1b [23];
  
  gp = 0x20004000;
  uStack_1c = FUN_ram_00066694(auStack_1b);
  thunk_FUN_ram_000521a0(0x2018,9,&uStack_1c);
  return 0;
}

