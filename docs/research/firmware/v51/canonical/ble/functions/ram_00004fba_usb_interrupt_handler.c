/* Address: ram:00004fba; name: usb_interrupt_handler; body bytes: 1344 */

/* USB endpoint events and descriptor/control transfers. */

void usb_interrupt_handler(void)

{
  byte bVar1;
  ushort uVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  byte bVar6;
  ushort uVar7;
  
  bVar3 = DAT_ram_40008006;
  gp = &DAT_ram_20002000;
  if ((DAT_ram_40008006 & 2) == 0) {
    if ((DAT_ram_40008006 & 1) == 0) {
      if ((DAT_ram_40008006 & 4) != 0) {
        if ((DAT_ram_40008005 & 4) != 0) {
          DAT_ram_20003a4a = 0;
          DAT_ram_20003a4b = 0;
          DAT_ram_20003a4d = 0;
          DAT_ram_20003a4c = 0;
          DAT_ram_20003a49 = 1;
        }
        DAT_ram_40008006 = 4;
      }
    }
    else {
      DAT_ram_40008003 = 0;
      DAT_ram_40008022 = 2;
      DAT_ram_40008026 = 0x12;
      DAT_ram_4000802a = 0x12;
      DAT_ram_4000802e = 0x12;
      DAT_ram_40008006 = 1;
    }
    goto LAB_ram_000052ec;
  }
  if ((DAT_ram_40008007 & 0x30) != 0x30) {
    bVar6 = DAT_ram_40008007 & 0x3f;
    if (bVar6 == 4) {
      if ((DAT_ram_40008007 & 0x40) != 0) {
        DAT_ram_40008032 = DAT_ram_40008032 ^ 0x80;
        FUN_ram_00004f90(DAT_ram_40008008);
      }
    }
    else if (bVar6 < 5) {
      if (bVar6 == 1) {
        if ((DAT_ram_40008007 & 0x40) != 0) {
          usb_receive_report();
        }
      }
      else if ((DAT_ram_40008007 & 0x3f) != 0) {
        if (bVar6 == 2) {
          if ((DAT_ram_40008007 & 0x40) != 0) {
            FUN_ram_00004f3c(DAT_ram_40008008);
          }
        }
        else if ((bVar6 == 3) && ((DAT_ram_40008007 & 0x40) != 0)) {
          FUN_ram_00004f66(DAT_ram_40008008);
        }
      }
    }
    else if (bVar6 == 0x22) {
      DAT_ram_4000802a = DAT_ram_4000802a & 0xfc | 2;
    }
    else if (bVar6 < 0x23) {
      if (bVar6 == 0x20) {
        if (DAT_ram_20002fc1 == 5) {
          DAT_ram_40008003 = DAT_ram_40008003 & 0x80 | (byte)DAT_ram_20002fc2;
        }
        else {
          if (DAT_ram_20002fc1 == 6) {
            uVar4 = (uint)DAT_ram_20002fc2;
            if (0x40 < uVar4) {
              uVar4 = 0x40;
            }
            FUN_ram_000078b2(DAT_ram_20002f50,DAT_ram_20002fc4,uVar4);
            DAT_ram_40008020 = (undefined1)uVar4;
            DAT_ram_20002fc2 = DAT_ram_20002fc2 - (short)uVar4;
            DAT_ram_20002fc4 = DAT_ram_20002fc4 + uVar4;
            DAT_ram_40008022 = DAT_ram_40008022 ^ 0x40;
            goto LAB_ram_00005014;
          }
          DAT_ram_40008020 = 0;
        }
        DAT_ram_40008022 = 2;
      }
      else if (bVar6 == 0x21) {
        DAT_ram_40008026 = DAT_ram_40008026 & 0xfc | 2;
        DAT_ram_20003a49 = 1;
      }
    }
    else if (bVar6 == 0x23) {
      DAT_ram_4000802e = DAT_ram_4000802e & 0xfc | 2;
    }
    else if (bVar6 == 0x24) {
      DAT_ram_40008032 = (DAT_ram_40008032 ^ 0x40) & 0xfc | 2;
    }
LAB_ram_00005014:
    DAT_ram_40008006 = 2;
  }
  if (-1 < (char)DAT_ram_40008007) goto LAB_ram_000052ec;
  DAT_ram_40008022 = 0xc2;
  DAT_ram_20002fc2 = *(ushort *)(DAT_ram_20002f50 + 6);
  DAT_ram_20002fc1 = DAT_ram_20002f50[1];
  bVar6 = *DAT_ram_20002f50;
  if ((bVar6 & 0x60) != 0) {
switchD_ram_00005082_caseD_2:
    DAT_ram_40008022 = 0xcf;
    goto LAB_ram_000052de;
  }
  switch(DAT_ram_20002fc1) {
  case 0:
    *DAT_ram_20002f50 = 0;
    DAT_ram_20002f50[1] = 0;
    uVar7 = 2;
    if (2 < DAT_ram_20002fc2) goto LAB_ram_00005388;
    break;
  case 1:
    if ((bVar6 & 0x1f) != 2) goto switchD_ram_00005082_caseD_2;
    bVar1 = DAT_ram_20002f50[4];
    if (bVar1 == 2) {
      DAT_ram_4000802a = DAT_ram_4000802a & 0x73;
    }
    else if (bVar1 < 3) {
      if (bVar1 != 1) goto switchD_ram_00005082_caseD_2;
      DAT_ram_40008026 = DAT_ram_40008026 & 0x73;
    }
    else if (bVar1 == 0x81) {
      DAT_ram_40008026 = DAT_ram_40008026 & 0xbc | 2;
    }
    else {
      if (bVar1 != 0x82) goto switchD_ram_00005082_caseD_2;
      DAT_ram_4000802a = DAT_ram_4000802a & 0xbc | 2;
    }
    break;
  default:
    goto switchD_ram_00005082_caseD_2;
  case 5:
    uVar7 = (ushort)DAT_ram_20002f50[2];
    goto LAB_ram_00005388;
  case 6:
    uVar7 = *(ushort *)(DAT_ram_20002f50 + 2);
    uVar2 = uVar7 >> 8;
    if (uVar2 == 2) {
      DAT_ram_20002fc4 = &DAT_ram_00008f70;
      iVar5 = 0;
      uVar7 = 0x29;
    }
    else if (uVar2 < 3) {
      if (uVar2 == 1) {
        DAT_ram_20002fc4 = &DAT_ram_00008f9c;
        iVar5 = 0;
        uVar7 = 0x12;
      }
      else {
LAB_ram_00005234:
        iVar5 = 0xff;
        uVar7 = 0;
      }
    }
    else if (uVar2 == 3) {
      if ((uVar7 & 0xff) == 1) {
        DAT_ram_20002fc4 = &DAT_ram_00008fb0;
        iVar5 = 0;
        uVar7 = 0xe;
      }
      else if ((uVar7 & 0xff) == 0) {
        DAT_ram_20002fc4 = &DAT_ram_00009304;
        iVar5 = 0;
        uVar7 = 4;
      }
      else {
        if ((uVar7 & 0xff) != 2) goto LAB_ram_00005234;
        DAT_ram_20002fc4 = &DAT_ram_20002e44;
        iVar5 = 0;
        uVar7 = (ushort)DAT_ram_20002e44;
      }
    }
    else {
      if (uVar2 != 0x22) goto LAB_ram_00005234;
      if (DAT_ram_20002f50[4] == 0) {
        DAT_ram_20002fc4 = &DAT_ram_00008f4c;
        iVar5 = 0;
        uVar7 = 0x23;
      }
      else {
        iVar5 = 0;
        uVar7 = 0xff;
      }
    }
    if (uVar7 < DAT_ram_20002fc2) {
      DAT_ram_20002fc2 = uVar7;
    }
    uVar4 = (uint)DAT_ram_20002fc2;
    if (0x40 < uVar4) {
      uVar4 = 0x40;
    }
    FUN_ram_000078b2(DAT_ram_20002f50,DAT_ram_20002fc4,uVar4);
    DAT_ram_20002fc4 = DAT_ram_20002fc4 + uVar4;
    if (iVar5 == 0xff) goto switchD_ram_00005082_caseD_2;
    break;
  case 8:
    *DAT_ram_20002f50 = DAT_ram_20002fc0;
    goto LAB_ram_0000539e;
  case 9:
    DAT_ram_20002fc0 = DAT_ram_20002f50[2];
    break;
  case 10:
    *DAT_ram_20002f50 = 0;
LAB_ram_0000539e:
    if (1 < DAT_ram_20002fc2) {
      uVar7 = 1;
LAB_ram_00005388:
      DAT_ram_20002fc2 = uVar7;
    }
  }
  DAT_ram_40008020 = 0;
  if ((char)bVar6 < '\0') {
    uVar7 = DAT_ram_20002fc2;
    if (0x40 < DAT_ram_20002fc2) {
      uVar7 = 0x40;
    }
    DAT_ram_20002fc2 = DAT_ram_20002fc2 - uVar7;
    DAT_ram_40008020 = (undefined1)uVar7;
  }
  DAT_ram_40008022 = 0xc0;
LAB_ram_000052de:
  DAT_ram_40008006 = 2;
LAB_ram_000052ec:
  if ((bVar3 & 0x20) != 0) {
    DAT_ram_20003a49 = 1;
  }
  return;
}

