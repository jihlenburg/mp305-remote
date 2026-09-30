/* Address: ram:00063bbc; name: RF_FrequencyHoppingTx; body bytes: 872 */

undefined4 RF_FrequencyHoppingTx(uint param_1)

{
  bool bVar1;
  byte bVar2;
  int iVar3;
  undefined1 *puVar4;
  int iVar5;
  undefined *puVar6;
  uint uVar7;
  undefined4 uVar8;
  char cVar9;
  undefined4 uStack_54;
  char cStack_50;
  undefined1 auStack_4f [6];
  undefined1 auStack_49 [6];
  undefined1 uStack_43;
  
  bVar2 = DAT_ram_20001eb4;
  gp = 0x20004000;
  DAT_ram_20001ee0 = 0;
  DAT_ram_20001eb4 = DAT_ram_20001eb4 | 1;
  iVar3 = tmos_snv_read(0x10,6,auStack_49);
  if ((iVar3 == 0) && (iVar3 = tmos_isbufset(auStack_49,0xff,6), iVar3 != 1)) {
    cStack_50 = '\x02';
    puVar6 = &DAT_ram_20001bd6;
    puVar4 = auStack_4f;
  }
  else {
    cStack_50 = '\x01';
    tmos_memcpy(auStack_4f,&DAT_ram_20001bd6,6);
    puVar6 = &UNK_ram_0006c28c;
    puVar4 = auStack_49;
  }
  tmos_memcpy(puVar4,puVar6,6);
  uStack_43 = FUN_ram_00061d68(DAT_ram_20001bd0);
  DAT_ram_20001eb5 = DAT_ram_20001ee3;
  DAT_ram_20001ebc = DAT_ram_20001ee8;
  DAT_ram_20001eec = (*DAT_ram_20001c00)();
  uStack_54 = 0xebe;
  do {
    do {
      RF_Tx(&cStack_50,0xe,cStack_50,5);
    } while ((DAT_ram_20001e96 & 1) == 0);
    DAT_ram_20001e96 = 0;
    FUN_ram_00062030((int)(uint)DAT_ram_20001eb4 >> 4 & 3,0x20,0);
    FUN_ram_200011be(1,(int)(uint)DAT_ram_20001eb4 >> 4 & 3,0xff);
    if ((DAT_ram_20001e97 & 1) != 0) {
      DAT_ram_20001e97 = 0;
      DAT_ram_20001e96 = 0;
      iVar5 = FUN_ram_20001120(DAT_ram_20001eac,0,0,0);
      iVar3 = DAT_ram_20001eac;
      if (((iVar5 == 0) && (*(char *)(DAT_ram_20001eac + 2) == '\x05')) &&
         (iVar5 = tmos_memcmp(DAT_ram_20001eac + 9,&DAT_ram_20001bd6,6), iVar5 == 1)) {
        *DAT_ram_20001ea8 = 6;
        FUN_ram_00061f0a((int)(uint)DAT_ram_20001eb4 >> 4 & 3,0);
        FUN_ram_200011be(3,(int)(uint)DAT_ram_20001eb4 >> 4 & 3,0);
        if ((DAT_ram_20001e96 & 1) != 0) {
          DAT_ram_20001e96 = 0;
          DAT_ram_20001edc = (*DAT_ram_20001c00)();
          RF_Shut();
          DAT_ram_20001ecd = *(undefined1 *)(iVar3 + 0x13);
          DAT_ram_20001eb5 = 0;
          DAT_ram_20001ee1 = 0;
          DAT_ram_20001ece = *(undefined1 *)(iVar3 + 0x14);
          bVar1 = false;
          DAT_ram_20001ecf = *(undefined1 *)(iVar3 + 0x15);
          DAT_ram_20001ebc = *(undefined4 *)(iVar3 + 0xf);
          DAT_ram_20001ec8 = *(uint *)(iVar3 + 0x16);
          DAT_ram_20001ee5 = '\0';
          uVar7 = 0;
          cVar9 = '\0';
          do {
            if ((DAT_ram_20001ec8 >> (uVar7 & 0x1f) & 1) != 0) {
              cVar9 = cVar9 + '\x01';
              bVar1 = true;
            }
            uVar7 = uVar7 + 1;
          } while (uVar7 != 0x20);
          if (bVar1) {
            DAT_ram_20001ee5 = cVar9;
          }
          DAT_ram_20001ecc = *(undefined1 *)(iVar3 + 0x1a);
          DAT_ram_20001ee0 = 2;
          DAT_ram_20001eb4 = bVar2;
          tmos_start_task(DAT_ram_20001ee4,4,0x28);
          if (cStack_50 != '\x01') {
            gp = 0x20004000;
            return 0;
          }
          FUN_ram_00042e5e(0x10,6,iVar3 + 3);
          FUN_ram_00042e10(1);
          gp = 0x20004000;
          return 0;
        }
      }
    }
    FUN_ram_00062262();
    if ((param_1 != 0) && (param_1 = param_1 - 1 & 0xff, param_1 == 0)) {
      RF_Shut();
      DAT_ram_20001eb4 = bVar2;
      return 1;
    }
    if (cStack_50 == '\x02') {
      *(undefined4 *)(DAT_ram_20001eb0 + 0xc) = 0xd00f;
      iVar3 = DAT_ram_20001eb0;
      fence.i();
      *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x2000;
      uVar8 = 0x6ee;
    }
    else {
      *(undefined4 *)(DAT_ram_20001eb0 + 0xc) = 0xd00f;
      iVar3 = DAT_ram_20001eb0;
      fence.i();
      *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x2000;
      uVar8 = uStack_54;
    }
    DAT_ram_20001e98 = 0x80;
    *(undefined4 *)(iVar3 + 100) = uVar8;
    *(undefined4 *)(iVar3 + 0xc) = 0xf00f;
    do {
    } while (*(int *)(DAT_ram_20001eb0 + 100) != 0);
    uVar7 = (*DAT_ram_20001c00)();
    if ((DAT_ram_20001bd2 < '\0') || (DAT_ram_20001eec <= uVar7)) {
      iVar3 = -DAT_ram_20001eec;
    }
    else {
      iVar3 = -0x57400000 - DAT_ram_20001eec;
    }
    if (32000 < uVar7 + iVar3) {
      FUN_ram_00042954();
      DAT_ram_20001eec = (*DAT_ram_20001c00)();
    }
  } while( true );
}

