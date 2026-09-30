/* Address: ram:000595ba; name: FUN_ram_000595ba; body bytes: 526 */

void FUN_ram_000595ba(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  
  iVar2 = DAT_ram_20001de8;
  gp = 0x20004000;
LAB_ram_000595f4:
  do {
    cVar1 = *(char *)(iVar2 + 6);
    if (cVar1 == -0x4e) {
      if ((DAT_ram_20001e94 & 1) == 0) {
        DAT_ram_20001e98 = 0;
        goto LAB_ram_0005961e;
      }
      DAT_ram_20001e94 = 0;
      iVar3 = FUN_ram_000592d2(iVar2);
    }
    else {
      if (cVar1 == -0x4c) {
        if ((DAT_ram_20001e95 & 1) == 0) {
          DAT_ram_20001e98 = 0;
        }
        else {
          DAT_ram_20001e95 = 0;
          iVar3 = (*DAT_ram_20001c00)();
          uVar5 = iVar3 + 8;
          if ((-1 < DAT_ram_20001bd2) && (0xa8bfffff < uVar5)) {
            uVar5 = iVar3 + 0x57400008;
          }
          *(uint *)(iVar2 + 0x60) = uVar5;
          FUN_ram_00058d92(iVar2);
          DAT_ram_20001e9b = 0;
        }
        goto LAB_ram_0005961e;
      }
      if (cVar1 == -0x4a) {
        *(undefined4 *)(DAT_ram_20001eb0 + 0xc) = 0xd00f;
        iVar3 = DAT_ram_20001eb0;
        fence.i();
        *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x2000;
        DAT_ram_20001e98 = 0x80;
        if ((*DAT_ram_20001e88 >> 0xc & 3) == 2) {
          uVar4 = 0x43e;
        }
        else if ((*DAT_ram_20001e88 >> 0xc & 3) == 0) {
          uVar4 = 0x196;
        }
        else {
          uVar4 = 0x1be;
        }
        *(undefined4 *)(iVar3 + 100) = uVar4;
        *(undefined4 *)(iVar3 + 0xc) = 0xf00f;
        FUN_ram_200010ec();
        if ((DAT_ram_20001e94 & 1) != 0) {
          DAT_ram_20001e94 = 0;
          FUN_ram_00062262();
          iVar3 = FUN_ram_000591f8(iVar2);
          if (iVar3 == 0) goto LAB_ram_0005961e;
        }
        *(char *)(iVar2 + 0x3e) = *(char *)(iVar2 + 0x3e) + '\x01';
        goto LAB_ram_0005961e;
      }
      if (cVar1 != -0x4d) {
        if (cVar1 != -0x4b) goto LAB_ram_0005961e;
        if ((DAT_ram_20001e95 & 1) == 0) {
          DAT_ram_20001e98 = 0;
          goto LAB_ram_0005961e;
        }
        DAT_ram_20001e95 = 0;
        if (*(byte *)(iVar2 + 0x3c) < 2) {
          iVar3 = (*DAT_ram_20001c00)();
          uVar5 = iVar3 + 8;
          if ((-1 < DAT_ram_20001bd2) && (0xa8bfffff < uVar5)) {
            uVar5 = iVar3 + 0x57400008;
          }
        }
        else {
          iVar3 = (*DAT_ram_20001c00)();
          uVar5 = iVar3 + 0x28;
          if ((-1 < DAT_ram_20001bd2) && (0xa8bfffff < uVar5)) {
            uVar5 = iVar3 + 0x57400028;
          }
        }
        *(uint *)(iVar2 + 0x60) = uVar5;
        *(undefined1 *)(iVar2 + 6) = 0xb6;
        goto LAB_ram_000595f4;
      }
      if ((DAT_ram_20001e94 & 1) == 0) goto LAB_ram_0005961e;
      DAT_ram_20001e94 = 0;
      iVar3 = FUN_ram_000590b8(iVar2);
    }
    if (iVar3 != 0) {
LAB_ram_0005961e:
      if (*(char *)(iVar2 + 4) == '\0') {
        return;
      }
      FUN_ram_000585c6();
      return;
    }
  } while( true );
}

