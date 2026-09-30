/* Address: ram:00007080; name: FUN_ram_00007080; body bytes: 102 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00007080(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 auStack_11 [13];
  
  gp = &DAT_ram_20002000;
  if (*(short *)(param_1 + 4) == DAT_ram_20002ffc) {
    _DAT_ram_20002ffc = 0xfffe;
    _DAT_ram_20003000 = 0;
    auStack_11[0] = 1;
    if ((DAT_ram_20002f89 == '\x02') || (DAT_ram_20002f8a == '\0')) {
      auStack_11[0] = 0;
    }
    (*_DAT_ram_00040174)(0x305,1,auStack_11,param_4,DAT_ram_20002f89,_DAT_ram_00040174);
    return;
  }
  return;
}

