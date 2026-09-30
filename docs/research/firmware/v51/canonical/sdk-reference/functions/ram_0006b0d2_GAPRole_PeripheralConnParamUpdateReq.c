/* Address: ram:0006b0d2; name: GAPRole_PeripheralConnParamUpdateReq; body bytes: 106 */

undefined4
GAPRole_PeripheralConnParamUpdateReq
          (undefined4 param_1,uint param_2,uint param_3,uint param_4,uint param_5,undefined4 param_6
          )

{
  int iVar1;
  undefined4 uVar2;
  undefined2 uStack_18;
  undefined2 uStack_16;
  undefined2 uStack_14;
  undefined2 uStack_12;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004df14();
  if (iVar1 == 0) {
    uVar2 = 0x14;
  }
  else if ((((*(ushort *)(iVar1 + 0xe) < param_2) || (param_3 < *(ushort *)(iVar1 + 0xe))) ||
           (*(ushort *)(iVar1 + 0x10) != param_4)) ||
          (uVar2 = 0x18, *(ushort *)(iVar1 + 0x12) != param_5)) {
    uStack_18 = (undefined2)param_2;
    uStack_16 = (undefined2)param_3;
    uStack_14 = (undefined2)param_4;
    uStack_12 = (undefined2)param_5;
    FUN_ram_0004de08(param_1,&uStack_18,param_6);
    uVar2 = 0;
  }
  return uVar2;
}

