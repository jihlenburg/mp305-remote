/* Address: 0001251c; name: FUN_0001251c; body bytes: 152 */

void FUN_0001251c(void)

{
  undefined1 auStack_28 [18];
  undefined2 local_16;
  undefined1 auStack_14 [12];
  
  FUN_00013be8(&DAT_00070700,0x10300);
  FUN_00013bf8(0);
  FUN_000151a4(1);
  FUN_00012260(auStack_14);
  FUN_00012222(&DAT_40040000,auStack_14);
  FUN_0001540c(auStack_28);
  local_16 = 0x8000;
  FUN_000152e0(0,8,auStack_28);
  FUN_000152e0(0,0x40,auStack_28);
  FUN_000121c4(&DAT_40040000,0,3,1);
  FUN_000121c4(&DAT_40040000,0,6,1);
  FUN_0001223c(&DAT_40040000,3,0x40);
  FUN_0001223c(&DAT_40040000,6,0x40);
  FUN_000121f8(&DAT_40040000,0x200);
  FUN_000121e4(&DAT_40040000,3,1);
  FUN_000121e4(&DAT_40040000,6,1);
  return;
}

