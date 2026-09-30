/* Address: ram:00068306; name: FUN_ram_00068306; body bytes: 828 */

uint FUN_ram_00068306(undefined4 param_1,uint param_2)

{
  byte bVar1;
  char cVar2;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined1 uStack_2c;
  undefined1 uStack_2b;
  undefined1 auStack_2a [6];
  undefined1 uStack_24;
  undefined1 uStack_23;
  
  gp = 0x20004000;
  if (-1 < (short)param_2) {
    if ((param_2 & 1) != 0) {
      if (DAT_ram_20001f14 != '\0') {
        uStack_2c = DAT_ram_20001f16;
        uStack_2b = DAT_ram_20001f24;
        tmos_memcpy(auStack_2a,&DAT_ram_20001ac4,6);
        uStack_24 = DAT_ram_20001f15;
        uStack_23 = DAT_ram_20001f49;
        iVar5 = FUN_ram_00047066(DAT_ram_200019cc,&uStack_2c);
        if (((iVar5 != 0) &&
            (DAT_ram_20001f20 = DAT_ram_20001f20 & 0xfffffff0 | 6,
            DAT_ram_20001a78 != (undefined4 *)0x0)) && ((code *)*DAT_ram_20001a78 != (code *)0x0)) {
          (*(code *)*DAT_ram_20001a78)();
        }
      }
      gp = 0x20004000;
      return param_2 ^ 1;
    }
    if ((param_2 & 2) != 0) {
      if ((((DAT_ram_20001f18 & 1) != 0) && (iVar5 = FUN_ram_0004737a(DAT_ram_200019cc), iVar5 != 0)
          ) && ((DAT_ram_20001f20 = DAT_ram_20001f20 & 0xffffff0f,
                DAT_ram_20001a78 != (undefined4 *)0x0 && ((code *)*DAT_ram_20001a78 != (code *)0x0))
               )) {
        (*(code *)*DAT_ram_20001a78)();
      }
      gp = 0x20004000;
      return param_2 ^ 2;
    }
    if ((param_2 & 4) == 0) {
      gp = 0x20004000;
      return 0;
    }
    if ((((DAT_ram_20001f53 != 0) && (iVar5 = FUN_ram_000473b6(DAT_ram_200019cc), iVar5 != 0)) &&
        (DAT_ram_20001f20 = DAT_ram_20001f20 & 0xfffff0ff, DAT_ram_20001a78 != (undefined4 *)0x0))
       && ((code *)*DAT_ram_20001a78 != (code *)0x0)) {
      (*(code *)*DAT_ram_20001a78)();
    }
    gp = 0x20004000;
    return param_2 ^ 4;
  }
  pcVar3 = (char *)tmos_msg_receive(DAT_ram_200019cc);
  if (pcVar3 == (char *)0x0) goto LAB_ram_00068358;
  if (*pcVar3 == -0x30) {
    bVar1 = pcVar3[2];
    if (bVar1 < 5) {
      if (bVar1 < 3) {
        if (bVar1 != 0) {
          if (bVar1 == 2) {
            cVar2 = pcVar3[3];
            if (pcVar3[1] == '\0') {
              if (cVar2 == '\x02') {
                DAT_ram_20001f20 = DAT_ram_20001f20 & 0xffffff0f | 0x20;
                cVar2 = FUN_ram_00047750(0,0);
              }
              else if (cVar2 == '\x01') {
                cVar2 = FUN_ram_00047640();
              }
              else {
                cVar2 = FUN_ram_00047530(0,0);
              }
              pcVar3[1] = cVar2;
            }
            else if (cVar2 != '\x02') {
              uVar4 = DAT_ram_20001f20 & 0xfffffff0 | 6;
              DAT_ram_20001f20 = uVar4;
              goto LAB_ram_00068448;
            }
          }
          goto LAB_ram_00068352;
        }
        if (pcVar3[1] == '\0') {
          tmos_memcpy(&DAT_ram_20001f4c,pcVar3 + 3,6);
          DAT_ram_20001f20 = 1;
          uVar6 = 1;
LAB_ram_000683de:
          tmos_set_event(DAT_ram_200019cc,uVar6);
          uVar4 = DAT_ram_20001f20;
        }
        else {
          DAT_ram_20001f20 = 6;
          uVar4 = DAT_ram_20001f20;
        }
      }
      else {
        uVar4 = DAT_ram_20001f20 & 0xfffffff0;
        if (pcVar3[1] == '\0') {
          if (bVar1 == 3) {
            uVar4 = uVar4 | 2;
            DAT_ram_20001f20 = uVar4;
            if ((char)DAT_ram_20001f18 < '\0') {
              DAT_ram_20001f18 = DAT_ram_20001f18 & 0x7f;
              uVar6 = 2;
              goto LAB_ram_000683de;
            }
          }
          else {
            DAT_ram_20001f14 = '\0';
            uVar4 = uVar4 | 3;
            DAT_ram_20001f20 = uVar4;
          }
        }
        else {
          uVar4 = uVar4 | 6;
          DAT_ram_20001f20 = uVar4;
        }
      }
    }
    else {
      if (bVar1 < 0x13) goto LAB_ram_00068352;
      if (bVar1 < 0x15) {
        uVar4 = DAT_ram_20001f20 & 0xffffff0f;
        if (pcVar3[1] == '\0') {
          if (bVar1 == 0x13) {
            DAT_ram_20001f20 = uVar4 | 0x10;
            if ((char)DAT_ram_20001f53 < '\0') {
              DAT_ram_20001f53 = DAT_ram_20001f53 & 0x7f;
              tmos_set_event(DAT_ram_200019cc,4);
            }
          }
          else {
            DAT_ram_20001f20 = uVar4 | 0x20;
          }
        }
        else {
          DAT_ram_20001f20 = uVar4 | 0x30;
        }
        uVar4 = 0x1000000;
      }
      else {
        if (1 < (byte)(bVar1 - 0x1b)) goto LAB_ram_00068352;
        uVar4 = DAT_ram_20001f20 & 0xfffff0ff;
        if (pcVar3[1] == '\0') {
          if (bVar1 == 0x1b) {
            DAT_ram_20001f20 = uVar4 | 0x100;
          }
          else {
            DAT_ram_20001f20 = uVar4 | 0x200;
          }
        }
        else {
          DAT_ram_20001f20 = uVar4 | 0x300;
        }
        uVar4 = 0x2000000;
      }
      uVar4 = uVar4 | DAT_ram_20001f20;
    }
LAB_ram_00068448:
    if ((DAT_ram_20001a78 != (undefined4 *)0x0) && ((code *)*DAT_ram_20001a78 != (code *)0x0)) {
      (*(code *)*DAT_ram_20001a78)(uVar4);
    }
  }
LAB_ram_00068352:
  tmos_msg_deallocate(pcVar3);
LAB_ram_00068358:
  return param_2 ^ 0x8000;
}

