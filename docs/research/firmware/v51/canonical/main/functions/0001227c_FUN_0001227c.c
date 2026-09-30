/* Address: 0001227c; name: FUN_0001227c; body bytes: 248 */

undefined8 FUN_0001227c(uint *param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  uint *local_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  
  local_20 = param_1;
  local_1c = param_2;
  if (DAT_1ffe0148 == '\x01') {
    local_18 = param_3;
    local_14 = param_4;
    FUN_000104ca(&DAT_1fff8c8c,&DAT_1fff8a8c,0x200);
    FUN_0001049c(&DAT_1fff8a8c,0x200);
    (&DAT_1fff8c8b)[DAT_1ffe014a] = 0;
    DAT_1ffe0148 = '\0';
    iVar1 = FUN_0001051e(&DAT_1fff8c8c,"VSET=",5);
    if (iVar1 == 0) {
      local_20 = &local_14;
      local_1c = 0;
      local_18 = 0;
      FUN_00010550(&DAT_1fff8c8c,"VSET=%d,ISET=%d,DCOUT_EN=%d",&local_18,&local_1c);
      if ((local_18 < 0x7725) && (local_1c < 0x13ed)) {
        set_voltage_raw((int)(local_18 + 5) / 10);
        set_current_raw(local_1c);
        FUN_0001aebc(local_14 & 0xff);
        return CONCAT44(local_1c,local_20);
      }
    }
    else {
      iVar1 = FUN_0001051e(&DAT_1fff8c8c,"TSET=",5);
      if (iVar1 == 0) {
        local_20 = (uint *)0x0;
        local_1c = 0;
        FUN_00010550(&DAT_1fff8c8c,"TSET=%d,%d",&local_20,&local_1c);
        DAT_1fffaa26 = (char)local_20;
        DAT_1fffaa27 = (char)local_1c;
        return CONCAT44(local_1c,local_20);
      }
      iVar1 = FUN_0001051e(&DAT_1fff8c8c,"FanCompareValue=",0x10);
      if (iVar1 == 0) {
        local_20 = (uint *)0x0;
        FUN_00010550(&DAT_1fff8c8c,"FanCompareValue=%d",&local_20);
        DAT_1fffaa06 = (short)local_20;
        return CONCAT44(local_1c,local_20);
      }
      iVar1 = FUN_0001051e(&DAT_1fff8c8c,"language=",9);
      if (iVar1 == 0) {
        local_20 = (uint *)0x0;
        FUN_00010550(&DAT_1fff8c8c,"language=%d",&local_20);
        DAT_1fffa0ce = SUB41(local_20,0);
        FUN_0001d958();
        FUN_0001ca60(200);
      }
    }
  }
  return CONCAT44(local_1c,local_20);
}

