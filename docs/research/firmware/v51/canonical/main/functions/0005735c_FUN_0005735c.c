/* Address: 0005735c; name: FUN_0005735c; body bytes: 848 */

undefined8 FUN_0005735c(uint param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  char *pcVar5;
  byte bVar6;
  uint uVar7;
  uint uVar8;
  
  if (DAT_1fffaaf3 != '\0' || param_1 != 0) {
    DAT_1fffab66 = 0;
    if (DAT_1ffe05b8 != 0) {
      if ((byte)(&DAT_1fffa340)[DAT_1fffa34a] < 0x65) {
        DAT_1fffaaf1 = 7;
      }
      else {
        DAT_1fffaaf1 = 9;
      }
      uVar3 = FUN_0004b9de(DAT_1ffe05b8,5);
      FUN_000499de(uVar3,"SRC Test - %dW",(&DAT_1fffa340)[DAT_1fffa34a]);
      param_1 = (*(ushort *)(&DAT_1fffa1da + (uint)DAT_1fffa34a * 0x24) >> 6) / 100;
      param_2 = (uint)(*(ushort *)(&DAT_1fffa1da + (uint)DAT_1fffa34a * 0x24) >> 6) % 100;
      uVar1 = *(ushort *)(&DAT_1fffa1d8 + (uint)DAT_1fffa34a * 0x24);
      uVar3 = FUN_0004b9de(DAT_1ffe05d4,0);
      uVar3 = FUN_0004b9de(uVar3,1);
      FUN_000499de(uVar3,"%02d.%02dV / %d.%02dA",(uVar1 >> 6) / 0x14,((uint)(uVar1 >> 6) * 5) % 100,
                   param_1,param_2,param_3,param_4);
      for (uVar7 = 1; bVar6 = DAT_1fffaaf1, uVar7 < DAT_1fffaaf1; uVar7 = uVar7 + 1 & 0xff) {
        if (((&DAT_1fffa1d8)[(uint)DAT_1fffa34a * 0x24 + uVar7 * 4] & 7) == 0) {
          uVar3 = FUN_0004b9de(DAT_1ffe05d4,uVar7);
          uVar3 = FUN_0004b9de(uVar3,0);
          FUN_0004e0e6(uVar3,1);
          uVar3 = FUN_0004b9de(DAT_1ffe05d4,uVar7);
          uVar3 = FUN_0004b9de(uVar3,0);
          uVar3 = FUN_0004b9de(uVar3,0);
          FUN_0004e0e6(uVar3,1);
          uVar3 = FUN_0004b9de(DAT_1ffe05d4,uVar7);
          uVar3 = FUN_0004b9de(uVar3,1);
          FUN_0004e0e6(uVar3,1);
        }
        else {
          uVar3 = FUN_0004b9de(DAT_1ffe05d4,uVar7);
          uVar3 = FUN_0004b9de(uVar3,0);
          FUN_0004aaf6(uVar3,1);
          uVar3 = FUN_0004b9de(DAT_1ffe05d4,uVar7);
          uVar3 = FUN_0004b9de(uVar3,0);
          uVar3 = FUN_0004b9de(uVar3,0);
          FUN_0004aaf6(uVar3,1);
          uVar3 = FUN_0004b9de(DAT_1ffe05d4,uVar7);
          uVar3 = FUN_0004b9de(uVar3,1);
          FUN_0004aaf6(uVar3,1);
          DAT_1fffab66 = DAT_1fffab66 | (ushort)(1 << uVar7);
        }
        if ((uVar7 < 5) || (uVar7 == 7)) {
          iVar2 = uVar7 * 4 + (uint)DAT_1fffa34a * 0x24;
          param_2 = (uint)(*(ushort *)(&DAT_1fffa138 + iVar2 + 0xa2) >> 6);
          param_1 = param_2 / 100;
          uVar8 = (uint)(*(ushort *)(&DAT_1fffa138 + iVar2 + 0xa0) >> 6);
          uVar4 = uVar8 * 5;
          uVar8 = uVar8 / 0x14;
          uVar3 = FUN_0004b9de(DAT_1ffe05d4,uVar7);
          uVar3 = FUN_0004b9de(uVar3,1);
          pcVar5 = "%02d.%02dV / %d.%02dA";
LAB_000575ea:
          param_2 = param_2 % 100;
          FUN_000499de(uVar3,pcVar5,uVar8,uVar4 % 100);
        }
        else if (uVar7 == 5) {
          uVar1 = *(ushort *)(&DAT_1fffa1ec + (uint)DAT_1fffa34a * 0x24);
          uVar8 = (uVar1 >> 9) / 0x14;
          param_2 = (uint)(byte)*(ushort *)(&DAT_1fffa1ee + (uint)DAT_1fffa34a * 0x24);
          param_1 = param_2 / 10;
          param_2 = param_2 % 10;
          uVar4 = (uint)(*(ushort *)(&DAT_1fffa1ee + (uint)DAT_1fffa34a * 0x24) >> 8);
          uVar3 = FUN_0004b9de(DAT_1ffe05d4,5);
          uVar3 = FUN_0004b9de(uVar3,1);
          FUN_000499de(uVar3,"%d.%d-%d.%dV / %d.%02dA",uVar4 / 10,uVar4 % 10,param_1,param_2,uVar8,
                       ((uint)(uVar1 >> 9) * 5) % 100);
        }
        else {
          if (uVar7 == 6) {
            uVar3 = FUN_0004b9de(DAT_1ffe05d4,6);
            FUN_0004e84a(uVar3,0xce,0x2e);
            param_2 = (uint)(*(ushort *)(&DAT_1fffa1f2 + (uint)DAT_1fffa34a * 0x24) >> 6);
            param_1 = param_2 / 100;
            uVar4 = (uint)(*(ushort *)(&DAT_1fffa1f0 + (uint)DAT_1fffa34a * 0x24) >> 6);
            uVar8 = uVar4 / 100;
            uVar3 = FUN_0004b9de(DAT_1ffe05d4,6);
            uVar3 = FUN_0004b9de(uVar3,1);
            pcVar5 = "09.0-15.0V / %d.%02dA\n15.0-20.0V / %d.%02dA";
            goto LAB_000575ea;
          }
          if (uVar7 == 8) {
            param_1 = (*(ushort *)(&DAT_1fffa1f8 + (uint)DAT_1fffa34a * 0x24) >> 7) / 10;
            param_2 = (uint)(*(ushort *)(&DAT_1fffa1f8 + (uint)DAT_1fffa34a * 0x24) >> 7) % 10;
            bVar6 = (&DAT_1fffa1fa)[(uint)DAT_1fffa34a * 0x24];
            uVar3 = FUN_0004b9de(DAT_1ffe05d4,8);
            uVar3 = FUN_0004b9de(uVar3,1);
            FUN_000499de(uVar3,"%d.%d-%d.%dV / %dW",bVar6 / 10,(uint)bVar6 % 10,param_1,param_2,
                         *(ushort *)(&DAT_1fffa1fa + (uint)DAT_1fffa34a * 0x24) >> 8);
          }
        }
        uVar3 = FUN_0004b9de(DAT_1ffe05d4,uVar7);
        FUN_0004e00e(uVar3,1);
      }
      for (; bVar6 < 9; bVar6 = bVar6 + 1) {
        uVar3 = FUN_0004b9de(DAT_1ffe05d4,bVar6);
        FUN_0004aa6e(uVar3,1);
      }
      if ((DAT_1fffaaf3 != '\0') && (DAT_1fffaacf != '\0')) {
        DAT_1fff9550 = DAT_1fff9550 | 0x400;
      }
    }
    DAT_1fffaaf3 = '\0';
  }
  return CONCAT44(param_2,param_1);
}

