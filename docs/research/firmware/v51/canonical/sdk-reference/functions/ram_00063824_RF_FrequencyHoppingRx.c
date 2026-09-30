/* Address: ram:00063824; name: RF_FrequencyHoppingRx; body bytes: 920 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 RF_FrequencyHoppingRx(int param_1)

{
  uint *puVar1;
  char *pcVar2;
  byte bVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  bool bVar9;
  char cVar10;
  char acStack_5d [13];
  undefined4 uStack_50;
  byte bStack_4c;
  undefined1 uStack_4b;
  undefined2 uStack_4a;
  uint uStack_48;
  undefined1 uStack_44;
  undefined1 uStack_43;
  
  bVar3 = DAT_ram_20001eb4;
  gp = 0x20004000;
  DAT_ram_20001eb4 = DAT_ram_20001eb4 | 1;
  _DAT_ram_20001ee0 = _DAT_ram_20001ee0 & 0xff00;
  DAT_ram_20001ebc = DAT_ram_20001ee8;
  DAT_ram_20001eb5 = DAT_ram_20001ee3;
  acStack_5d[1] = 5;
  tmos_memcpy(acStack_5d + 2,&DAT_ram_20001bd6,6);
  uVar5 = BLE_AccessAddressGenerate();
  uStack_50 = CONCAT13((char)((uint)uVar5 >> 0x10),
                       CONCAT12((char)((uint)uVar5 >> 8),(undefined2)uStack_50));
  uStack_50._0_2_ = CONCAT11((char)uVar5,(undefined1)uStack_50);
  uStack_4b = DAT_ram_20001ecd;
  bStack_4c = (byte)((uint)uVar5 >> 0x18);
  uStack_4a = _DAT_ram_20001ece;
  uStack_48 = DAT_ram_20001ec8;
  uStack_44 = DAT_ram_20001ecc;
  uStack_43 = FUN_ram_00061d68(DAT_ram_20001bd0);
  bVar9 = false;
  uVar4 = 0;
  if (param_1 != 0) {
    iVar6 = (*DAT_ram_20001c00)();
    bVar9 = true;
    uVar4 = param_1 * 0x20 + iVar6;
    if ((-1 < DAT_ram_20001bd2) && (0xa8bfffff < uVar4)) {
      uVar4 = uVar4 + 0x57400000;
    }
  }
  DAT_ram_20001eec = (*DAT_ram_20001c00)();
  iVar6 = RF_Rx(acStack_5d + 1,0x1a,0xff,5);
  if (iVar6 != 0) {
    return 1;
  }
  do {
    if ((DAT_ram_20001e99 & 1) != 0) {
      FUN_ram_200010ec();
      pcVar2 = DAT_ram_20001eac;
      if ((DAT_ram_20001e94 & 1) != 0) {
        acStack_5d[0] = '\0';
        DAT_ram_20001e94 = 0;
        iVar7 = FUN_ram_20001120(DAT_ram_20001eac,0,acStack_5d,0);
        iVar6 = DAT_ram_20001ed8;
        if ((iVar7 == 0) &&
           ((pcVar2[2] == '\x01' ||
            ((pcVar2[2] == '\x02' &&
             (iVar7 = tmos_memcmp(pcVar2 + 9,&DAT_ram_20001bd6,6), iVar7 == 1)))))) {
          if (uStack_48 == 0) {
            FUN_ram_00062262();
            DAT_ram_20001ec8 = 0xffffffff;
            FUN_ram_200012e0((int)acStack_5d[0],&DAT_ram_20001ec8);
            uVar8 = FUN_ram_000582da(&DAT_ram_20001ec8);
            if (4 < uVar8) {
              uStack_48 = DAT_ram_20001ec8;
            }
          }
          else {
            tmos_memcpy(iVar6 + 9,pcVar2 + 3,6);
            FUN_ram_00061f0a((int)(uint)DAT_ram_20001eb4 >> 4 & 3,
                             *(undefined1 *)(DAT_ram_20001ed8 + 1));
            puVar1 = DAT_ram_20001e88;
            *DAT_ram_20001e88 = *DAT_ram_20001e88 | 0x800000;
            puVar1[0xb] = puVar1[0xb] & 0xfffffffc;
            FUN_ram_200010ec();
            if ((DAT_ram_20001e95 & 1) != 0) {
              DAT_ram_20001e95 = 0;
              *(undefined4 *)(DAT_ram_20001eb0 + 0xc) = 0xd00f;
              iVar6 = DAT_ram_20001eb0;
              puVar1 = DAT_ram_20001e88;
              fence.i();
              *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x2000;
              DAT_ram_20001e98 = 0x80;
              if ((*puVar1 >> 0xc & 3) == 2) {
                uVar5 = 0x43e;
              }
              else if ((*puVar1 >> 0xc & 3) == 0) {
                uVar5 = 0x196;
              }
              else {
                uVar5 = 0x1be;
              }
              *(undefined4 *)(iVar6 + 100) = uVar5;
              *(undefined4 *)(iVar6 + 0xc) = 0xf00f;
              FUN_ram_200010ec();
              if (((DAT_ram_20001e94 & 1) != 0) &&
                 (DAT_ram_20001e94 = 0, *DAT_ram_20001eac == '\x06')) {
                DAT_ram_20001edc = (*DAT_ram_20001c00)();
                RF_Shut();
                DAT_ram_20001eb5 = 0;
                DAT_ram_20001ee5 = '\0';
                DAT_ram_20001ebc = (uint)bStack_4c << 0x18 | uStack_50 >> 8;
                _DAT_ram_20001ee0 = 4;
                bVar9 = false;
                uVar4 = 0;
                cVar10 = '\0';
                do {
                  if ((DAT_ram_20001ec8 >> (uVar4 & 0x1f) & 1) != 0) {
                    cVar10 = cVar10 + '\x01';
                    bVar9 = true;
                  }
                  uVar4 = uVar4 + 1;
                } while (uVar4 != 0x20);
                if (bVar9) {
                  DAT_ram_20001ee5 = cVar10;
                }
                DAT_ram_20001eb4 = bVar3;
                tmos_set_event(DAT_ram_20001ee4,2);
                gp = 0x20004000;
                return 0;
              }
            }
          }
        }
      }
      RF_Rx(acStack_5d + 1,0x1a,0xff,5);
    }
    if (bVar9) {
      uVar8 = (*DAT_ram_20001c00)();
      if (uVar8 < uVar4) {
        if ((int)(uVar4 - uVar8) < 0) {
LAB_ram_00063b1a:
          RF_Shut();
          gp = 0x20004000;
          DAT_ram_20001eb4 = bVar3;
          return 1;
        }
      }
      else if (-1 < (int)(uVar8 - uVar4)) goto LAB_ram_00063b1a;
    }
    uVar8 = (*DAT_ram_20001c00)();
    if ((DAT_ram_20001bd2 < '\0') || (DAT_ram_20001eec <= uVar8)) {
      iVar6 = -DAT_ram_20001eec;
    }
    else {
      iVar6 = -0x57400000 - DAT_ram_20001eec;
    }
    if (32000 < uVar8 + iVar6) {
      FUN_ram_00042954();
      DAT_ram_20001eec = (*DAT_ram_20001c00)();
      RF_Rx(acStack_5d + 1,0x1a,0xff,5);
    }
  } while( true );
}

