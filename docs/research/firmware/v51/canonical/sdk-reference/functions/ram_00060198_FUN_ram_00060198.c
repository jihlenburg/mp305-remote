/* Address: ram:00060198; name: FUN_ram_00060198; body bytes: 582 */

void FUN_ram_00060198(void)

{
  int iVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  char cVar5;
  
  iVar1 = DAT_ram_20001dd8;
  gp = 0x20004000;
  do {
    while( true ) {
      cVar5 = *(char *)(iVar1 + 10);
      if (cVar5 == -0x5e) {
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
          iVar3 = FUN_ram_0005fdd2(iVar1);
          if (iVar3 != 0) {
            if (*(char *)(iVar1 + 0x14) < '\0') {
              cVar5 = *(byte *)(iVar1 + 0x13) << 1;
              if ((*(byte *)(iVar1 + 0x13) & 0x7f) == 0) {
                cVar5 = -1;
              }
              *(char *)(iVar1 + 0x13) = cVar5;
            }
            else {
              *(undefined1 *)(iVar1 + 0x14) = 0xff;
            }
            uVar2 = FUN_ram_000428ec(1,*(undefined1 *)(iVar1 + 0x13));
            *(undefined1 *)(iVar1 + 0x11) = uVar2;
          }
        }
        goto LAB_ram_00060258;
      }
      if (cVar5 == -0x5f) break;
      if (cVar5 == -0x5a) {
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
        if ((DAT_ram_20001e94 & 1) == 0) {
LAB_ram_00060338:
          if (*(char *)(iVar1 + 0x14) < '\0') {
            cVar5 = *(byte *)(iVar1 + 0x13) << 1;
            if ((*(byte *)(iVar1 + 0x13) & 0x7f) == 0) {
              cVar5 = -1;
            }
            *(char *)(iVar1 + 0x13) = cVar5;
          }
          else {
            *(undefined1 *)(iVar1 + 0x14) = 0xff;
          }
          uVar2 = FUN_ram_000428ec(1,*(undefined1 *)(iVar1 + 0x13));
          *(undefined1 *)(iVar1 + 0x11) = uVar2;
        }
        else {
          DAT_ram_20001e94 = 0;
          FUN_ram_00062262();
          iVar3 = FUN_ram_0005f592(iVar1);
          if (iVar3 != 0) goto LAB_ram_00060338;
        }
        if (*(char *)(iVar1 + 10) == -0x5b) {
          FUN_ram_0005e3f4();
        }
        goto LAB_ram_00060258;
      }
      if (cVar5 == -0x5c) {
        FUN_ram_200010ec();
        if ((DAT_ram_20001e94 & 1) != 0) {
          DAT_ram_20001e94 = 0;
          FUN_ram_0005ef72(iVar1);
        }
        if (*(char *)(iVar1 + 10) == -0x5b) goto LAB_ram_000603b6;
      }
      else {
        if (cVar5 != -0x5b) goto LAB_ram_00060258;
LAB_ram_000603b6:
        FUN_ram_0005e3f4();
      }
      if (*(char *)(iVar1 + 10) != -0x5a) goto LAB_ram_00060258;
    }
    if ((DAT_ram_20001e94 & 1) == 0) {
      DAT_ram_20001e98 = 0;
      break;
    }
    DAT_ram_20001e94 = 0;
    FUN_ram_0005f942(iVar1);
  } while (*(char *)(iVar1 + 10) != -0x5f);
LAB_ram_00060258:
  if (*(char *)(iVar1 + 8) == '\0') {
    return;
  }
  FUN_ram_0005fea2();
  return;
}

