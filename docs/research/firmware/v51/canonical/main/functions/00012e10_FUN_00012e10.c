/* Address: 00012e10; name: FUN_00012e10; body bytes: 114 */

void FUN_00012e10(void)

{
  undefined1 uStack_28;
  undefined1 local_27;
  undefined1 local_26;
  undefined1 local_25;
  undefined4 local_20;
  undefined4 local_18;
  undefined2 local_14;
  undefined2 local_12;
  undefined2 local_10;
  undefined2 local_e;
  
  FUN_0001518c(0x200000);
  FUN_0001df1c(&uStack_28);
  local_26 = 0;
  local_25 = 2;
  local_27 = 0x60;
  local_20 = 0x927c;
  FUN_0001de48(&DAT_4003a400,&uStack_28);
  FUN_0001dee4(&local_18);
  local_14 = 0;
  local_10 = 0;
  local_18 = 0;
  local_12 = 0;
  local_e = 1;
  FUN_000153b4(1,0x800,4);
  FUN_0001de7e(&DAT_4003a400,3,&local_18);
  FUN_0001deba(&DAT_4003a400,3,1);
  FUN_00012e00();
  return;
}

