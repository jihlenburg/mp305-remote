/* Address: ram:00065aec; name: FUN_ram_00065aec; body bytes: 294 */

undefined4 FUN_ram_00065aec(uint param_1,int param_2,int param_3,char param_4)

{
  bool bVar1;
  byte *pbVar2;
  uint uVar3;
  byte bVar4;
  undefined4 uVar5;
  byte *pbVar6;
  byte *pbVar7;
  
  pbVar2 = DAT_ram_20001ea8;
  gp = 0x20004000;
  if (param_1 == 0) {
    uVar3 = 0x25;
  }
  else if (param_1 < 0xc) {
    uVar3 = param_1 - 1;
LAB_ram_00065b1a:
    uVar3 = uVar3 & 0xff;
  }
  else if (param_1 == 0xc) {
    uVar3 = 0x26;
  }
  else {
    if (param_1 < 0x27) {
      uVar3 = param_1 - 2;
      goto LAB_ram_00065b1a;
    }
    bVar1 = param_1 != 0x27;
    uVar3 = param_1;
    param_1 = 0x12;
    if (bVar1) {
      gp = 0x20004000;
      return 0x12;
    }
  }
  if (param_3 == 0) {
    pbVar7 = DAT_ram_20001ea8 + param_2;
    for (pbVar6 = DAT_ram_20001ea8; pbVar7 != pbVar6; pbVar6 = pbVar6 + 1) {
      bVar4 = FUN_ram_000659f4();
      pbVar6[2] = bVar4;
    }
  }
  else {
    if (param_3 == 1) {
      uVar5 = 0xf0;
    }
    else if (param_3 == 2) {
      uVar5 = 0xaa;
    }
    else {
      if (param_3 == 3) {
        pbVar7 = DAT_ram_20001ea8 + param_2;
        for (pbVar6 = DAT_ram_20001ea8; pbVar7 != pbVar6; pbVar6 = pbVar6 + 1) {
          param_1 = FUN_ram_00065a42(param_1);
          pbVar6[2] = (byte)param_1;
        }
        goto LAB_ram_00065b2c;
      }
      if (param_3 == 4) {
        uVar5 = 0xff;
      }
      else if (param_3 == 5) {
        uVar5 = 0;
      }
      else if (param_3 == 6) {
        uVar5 = 0xf;
      }
      else {
        if (param_3 != 7) {
          gp = 0x20004000;
          return 0x12;
        }
        uVar5 = 0x55;
      }
    }
    tmos_memset(DAT_ram_20001ea8 + 2,uVar5,param_2);
  }
LAB_ram_00065b2c:
  *pbVar2 = (byte)param_3 & 0xf;
  pbVar2[1] = (byte)param_2;
  FUN_ram_00062394(uVar3,1,param_2,param_4 + -1);
  return 0;
}

