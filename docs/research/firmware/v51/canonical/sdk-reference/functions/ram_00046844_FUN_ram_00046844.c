/* Address: ram:00046844; name: FUN_ram_00046844; body bytes: 294 */

undefined4 FUN_ram_00046844(undefined1 *param_1)

{
  char cVar1;
  byte bVar2;
  undefined4 uVar3;
  char cStack_2d;
  undefined1 uStack_2c;
  undefined1 uStack_2b;
  undefined2 uStack_28;
  undefined2 uStack_26;
  undefined2 uStack_24;
  undefined2 uStack_22;
  
  gp = 0x20004000;
  if (DAT_ram_20001a04 == 0) {
    uVar3 = 0x12;
    if ((DAT_ram_20001d50 & 10) != 0) {
      DAT_ram_20001a04 = FUN_ram_20000040(4,0x471d);
      uVar3 = 0x13;
      if (DAT_ram_20001a04 != 0) {
        DAT_ram_20001d53 = *param_1;
        tmos_memcpy(DAT_ram_20001a04,param_1,4);
        GAPBondMgr_GetParameter(0x41f,&cStack_2d);
        cVar1 = DAT_ram_20001c06 != '\0';
        if (cStack_2d != '\0') {
          cVar1 = cVar1 + '\x02';
        }
        bVar2 = GAP_GetParamValue(0x21);
        if ((bVar2 & 1) == 0) {
          if ((bVar2 & 4) == 0) {
            gp = 0x20004000;
            return 0x18;
          }
          uStack_2c = param_1[2];
          uStack_28 = GAP_GetParamValue(0x22);
          uStack_24 = GAP_GetParamValue(0x23);
        }
        else {
          uStack_28 = GAP_GetParamValue(5);
          uStack_2c = param_1[2];
          uStack_24 = GAP_GetParamValue(6);
          if ((bVar2 & 4) != 0) {
            uStack_2b = param_1[2];
            uStack_26 = GAP_GetParamValue(0x22);
            uStack_22 = GAP_GetParamValue(0x23);
          }
        }
        uVar3 = thunk_FUN_ram_00065922(cVar1,param_1[3],bVar2,&uStack_2c,&uStack_28,&uStack_24);
      }
    }
  }
  else {
    uVar3 = 0x11;
  }
  return uVar3;
}

