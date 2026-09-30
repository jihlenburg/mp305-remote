/* Address: 0001f2f0; name: FUN_0001f2f0; body bytes: 136 */

void FUN_0001f2f0(void)

{
  undefined1 uStack_40;
  undefined1 local_3f;
  undefined1 local_3e;
  undefined1 local_3d;
  undefined4 local_38;
  undefined4 local_30;
  undefined2 local_2c;
  undefined2 local_2a;
  undefined2 local_28;
  undefined2 local_26;
  undefined1 auStack_24 [20];
  
  FUN_0001540c(auStack_24);
  FUN_000152e0(0,0x100,auStack_24);
  FUN_0001518c(0x100000);
  FUN_0001df1c(&uStack_40);
  local_3e = 0;
  local_3d = 2;
  local_3f = 0x20;
  local_38 = 0x400;
  FUN_0001de48(&DAT_4003a000,&uStack_40);
  FUN_0001dee4(&local_30);
  local_28 = 0;
  local_2c = 0;
  local_26 = 1;
  local_30 = 0;
  local_2a = 0;
  FUN_000153b4(0,0x100,4);
  FUN_0001de7e(&DAT_4003a000,0,&local_30);
  FUN_0001deba(&DAT_4003a000,0,1);
  FUN_0001df10(&DAT_4003a000);
  return;
}

