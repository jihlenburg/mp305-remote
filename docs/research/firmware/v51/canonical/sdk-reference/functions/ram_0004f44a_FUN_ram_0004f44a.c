/* Address: ram:0004f44a; name: FUN_ram_0004f44a; body bytes: 180 */

uint FUN_ram_0004f44a(undefined4 param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  gp = 0x20004000;
  if ((short)param_2 < 0) {
    iVar2 = tmos_msg_receive(DAT_ram_20001d4f);
    if (iVar2 != 0) {
      iVar3 = FUN_ram_0004ed8c();
      if ((iVar3 == 0) && (DAT_ram_20001d4e != -1)) {
        tmos_msg_send();
      }
      else {
        tmos_msg_deallocate(iVar2);
      }
    }
    param_2 = param_2 ^ 0x8000;
  }
  else if ((param_2 & 1) == 0) {
    if (param_2 != 0) {
      for (uVar1 = 1; uVar4 = FUN_ram_0004e0b2(), uVar1 < uVar4; uVar1 = uVar1 + 1 & 0xff) {
        uVar4 = 1 << (uVar1 & 0x1f) & 0xffff;
        if ((param_2 & uVar4) != 0) {
          iVar2 = FUN_ram_0004e354(uVar4);
          if (iVar2 != 0xffff) {
            FUN_ram_0004e5a2(iVar2,0x17);
          }
          gp = 0x20004000;
          return param_2 ^ uVar4;
        }
      }
    }
    param_2 = 0;
  }
  else {
    FUN_ram_0004e636();
    param_2 = param_2 ^ 1;
  }
  return param_2;
}

