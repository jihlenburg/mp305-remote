/* Address: ram:00049f9e; name: GATTServApp_ProcessCCCWriteReq; body bytes: 96 */

undefined4
GATTServApp_ProcessCCCWriteReq
          (undefined4 param_1,int param_2,ushort *param_3,int param_4,int param_5,uint param_6)

{
  ushort uVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  
  gp = 0x20004000;
  if (param_5 == 0) {
    uVar4 = 0xd;
    if (param_4 == 2) {
      uVar1 = *param_3;
      if ((~param_6 & (uint)uVar1) == 0) {
        uVar2 = *(undefined4 *)(param_2 + 0xc);
        uVar3 = GATTServApp_ReadCharCfg(param_1,uVar2);
        uVar4 = 0;
        if (uVar1 != uVar3) {
          uVar4 = GATTServApp_WriteCharCfg(param_1,uVar2);
          return uVar4;
        }
      }
      else {
        uVar4 = 0x80;
      }
      return uVar4;
    }
  }
  else {
    uVar4 = 0xb;
  }
  return uVar4;
}

