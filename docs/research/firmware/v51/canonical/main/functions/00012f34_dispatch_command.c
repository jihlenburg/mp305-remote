/* Address: 00012f34; name: dispatch_command; body bytes: 1082 */

void dispatch_command(int param_1)

{
  int iVar1;
  byte bVar2;
  char cVar3;
  undefined1 *puVar4;
  int iVar5;
  undefined1 *puVar6;
  int iVar7;
  undefined1 *puVar8;
  uint uVar9;
  uint uVar10;
  
  if ((((DAT_1ffe01ac != '\x01') && (DAT_1ffe01ad != '\x01')) && (DAT_1ffe01ae != '\x01')) &&
     (DAT_1ffe01af != '\x01')) goto switchD_0001304e_caseD_dd;
  puVar4 = (undefined1 *)FUN_00015fa4(1);
  puVar8 = puVar4 + 4;
  iVar5 = 0;
  if (DAT_1ffe01ac == '\0') {
    if (DAT_1ffe01ad == '\0') {
      if (DAT_1ffe01ae == '\0') {
        iVar5 = 3;
        DAT_1ffe01af = '\0';
      }
      else {
        iVar5 = 2;
        DAT_1ffe01ae = '\0';
      }
    }
    else {
      iVar5 = 1;
      DAT_1ffe01ad = '\0';
    }
  }
  else {
    DAT_1ffe01ac = '\0';
  }
  iVar1 = iVar5 * 0x104;
  puVar6 = &DAT_1fff9664 + iVar1;
  uVar10 = (uint)(byte)(&DAT_1fff9662)[iVar1];
  bVar2 = (&DAT_1fff9664)[iVar1];
  cVar3 = (&DAT_1fff9660)[iVar5 * 0x104];
  uVar9 = 0;
  if (cVar3 == '\x01') {
    if (DAT_1fffaacf != '\x02') {
      DAT_1ffe01a4 = DAT_1fff9b54;
    }
    DAT_1fffaacf = '\x02';
    DAT_1ffe01a8 = 0;
  }
  if (bVar2 == 0xda) {
    iVar7 = cmd_da(puVar6,uVar10,puVar8,cVar3);
LAB_00013240:
    DAT_1fffab17 = 1;
LAB_000131b6:
    FUN_0001aebc(0);
    goto LAB_000131bc;
  }
  if (bVar2 < 0xdb) {
    if (bVar2 == 0xbe) {
      cmd_be(puVar6,uVar10);
      goto switchD_0001304e_caseD_dd;
    }
    if (bVar2 < 0xbf) {
      if (bVar2 == 0x53) {
        if ((cVar3 != '\x03') || ((&DAT_1fff9665)[iVar1] != '\0')) goto switchD_0001304e_caseD_dd;
        DAT_1fff954c = '\0';
LAB_00013148:
        DAT_1fff9440 = 1000;
        goto switchD_0001304e_caseD_dd;
      }
      if (bVar2 < 0x54) {
        if (bVar2 == 0) {
          iVar7 = cmd_00();
        }
        else {
          if (bVar2 == 0x18) {
            bind_pending = 1;
            DAT_1ffe018a = cVar3;
            goto switchD_0001304e_caseD_dd;
          }
          if (bVar2 != 0x20) {
            if (((bVar2 != 0x51) || (cVar3 != '\x03')) || ((&DAT_1fff9665)[iVar1] != '\0'))
            goto switchD_0001304e_caseD_dd;
            DAT_1fff954b = '\0';
            goto LAB_00013148;
          }
          iVar7 = cmd_20();
        }
      }
      else if (bVar2 == 0xa0) {
        *puVar8 = 0xa1;
        iVar7 = 2;
        puVar4[5] = DAT_1fffa0ce;
        if (cVar3 == '\x06') {
          iVar7 = 3;
          puVar4[6] = puVar6[uVar10 - 1];
        }
      }
      else {
        if (bVar2 != 0xa2) {
          if (bVar2 == 0xbb) {
            cmd_bb(puVar6,uVar10);
          }
          else if (bVar2 == 0xbd) {
            cmd_bd(puVar6,uVar10);
          }
          goto switchD_0001304e_caseD_dd;
        }
        iVar7 = cmd_a2_language(puVar6,uVar10,puVar8,cVar3);
      }
    }
    else if (bVar2 == 0xd0) {
      iVar7 = cmd_d0(puVar6,uVar10,puVar8,cVar3);
    }
    else if (bVar2 < 0xd1) {
      if (bVar2 == 0xc2) {
        iVar7 = cmd_c2_telemetry(puVar6,uVar10,puVar8,cVar3);
      }
      else if (bVar2 == 0xc4) {
        iVar7 = cmd_c4_read_settings(puVar6,uVar10,puVar8,cVar3);
      }
      else if (bVar2 == 0xc6) {
        iVar7 = cmd_c6_write_settings(puVar6,uVar10,puVar8,cVar3);
      }
      else {
        if (bVar2 != 200) goto switchD_0001304e_caseD_dd;
        iVar7 = cmd_c8_dc_control(puVar6,uVar10,puVar8,cVar3);
      }
    }
    else {
      if (bVar2 == 0xd2) {
        iVar7 = cmd_d2(puVar6,uVar10,puVar8,cVar3);
        goto LAB_00013240;
      }
      if (bVar2 != 0xd4) {
        if (bVar2 != 0xd6) {
          if (bVar2 == 0xd8) {
            DAT_1ffe0187 = 0;
            do {
              if ((&DAT_1fffa3fe)[uVar9] == (&DAT_1fff9665)[iVar1]) {
                DAT_1ffe0188 = (undefined1)uVar9;
                if (uVar9 < 10) {
                  DAT_1fffa8ca = 1;
                  goto LAB_0001321a;
                }
                break;
              }
              uVar9 = uVar9 + 1 & 0xff;
            } while (uVar9 < 10);
            DAT_1fffa8ca = 0;
LAB_0001321a:
            DAT_1ffe0189 = puVar6[uVar10 - 1];
          }
          goto switchD_0001304e_caseD_dd;
        }
        iVar7 = cmd_d6(puVar6,uVar10,puVar8,cVar3);
        DAT_1fffa8cc = 0;
        goto LAB_000131b6;
      }
      iVar7 = cmd_d4(puVar6,uVar10,puVar8,cVar3);
    }
    goto LAB_000131bc;
  }
  switch(bVar2) {
  case 0xdc:
    iVar7 = cmd_dc(puVar6,uVar10,puVar8,cVar3);
    break;
  default:
    goto switchD_0001304e_caseD_dd;
  case 0xde:
    iVar7 = cmd_de(puVar6,uVar10,puVar8,cVar3);
    break;
  case 0xe0:
    iVar7 = cmd_e0_device_info();
    break;
  case 0xe1:
    handle_e1(puVar6,uVar10,puVar8,cVar3);
    goto switchD_0001304e_caseD_dd;
  case 0xe2:
    iVar7 = cmd_e2(puVar6,uVar10,puVar8,cVar3);
    break;
  case 0xe4:
    iVar7 = cmd_e4(puVar6,uVar10,puVar8,cVar3);
    break;
  case 0xe8:
    iVar7 = cmd_e8(puVar6,uVar10,puVar8,cVar3);
    break;
  case 0xea:
    iVar7 = cmd_ea(puVar6,uVar10,puVar8,cVar3);
    break;
  case 0xec:
    iVar7 = cmd_ec(puVar6,uVar10,puVar8,cVar3);
    break;
  case 0xee:
    iVar7 = cmd_ee(puVar6,uVar10,puVar8,cVar3);
    break;
  case 0xf0:
    iVar7 = cmd_f0();
    break;
  case 0xf1:
    if (((cVar3 == '\x03') && ((&DAT_1fff9665)[iVar1] == '\0')) && (DAT_1fffa00e == '\x01')) {
      DAT_1fffa00e = '\x02';
    }
    goto switchD_0001304e_caseD_dd;
  case 0xf2:
    iVar7 = cmd_f2();
    break;
  case 0xf4:
    iVar7 = cmd_f4();
    break;
  case 0xf6:
    iVar7 = cmd_f6();
    break;
  case 0xfc:
    iVar7 = cmd_fc();
    break;
  case 0xfd:
    if ((&DAT_1fff9665)[iVar1] == '\x03') {
      DAT_1ffe018d = 0;
      DAT_1fff9449 = 1;
      FUN_0001ae70(1);
      DAT_1fff9438 = 1;
      DAT_1fff9550 = DAT_1fff9550 | 0x2000;
    }
    else if ((&DAT_1fff9665)[iVar1] == -1) {
      DAT_1fff9449 = 0;
      DAT_1ffe0186 = 0;
      DAT_1ffe0185 = 0;
      DAT_1ffe0184 = 1;
      DAT_1fff9438 = 0;
      DAT_1fff943c = DAT_1fff943c + 1;
    }
    goto switchD_0001304e_caseD_dd;
  case 0xfe:
    iVar7 = cmd_fe();
  }
LAB_000131bc:
  if (iVar7 != 0) {
    puVar4[2] = (char)iVar7;
    puVar4[1] = (&DAT_1fff9660)[iVar5 * 0x104];
    *puVar4 = (&DAT_1fff9661)[iVar1];
    DAT_1fff954a = encode_transport_frame(1,puVar4,&DAT_1fff944a);
    DAT_1fff9448 = 1;
  }
switchD_0001304e_caseD_dd:
  if ((DAT_1fffaacf == '\x02') &&
     ((DAT_1ffe01a8 = param_1 + DAT_1ffe01a8, 8000 < DAT_1ffe01a8 ||
      (((DAT_1fff9b9a == '\0' && (DAT_1fff9b54 < 3000)) && (DAT_1fff9b54 + 500 < (uint)DAT_1ffe01a4)
       ))))) {
    DAT_1fffaacf = '\0';
    DAT_1ffe01a8 = 0;
    DAT_1ffe0185 = 0;
    DAT_1ffe0198 = 0;
  }
  if (((DAT_1fff954b != '\0') || (DAT_1fff954c != '\0')) &&
     (DAT_1fff9440 = DAT_1fff9440 - param_1, DAT_1fff9440 < 1)) {
    if (DAT_1fff954b != '\0') {
      DAT_1ffe018c = 0;
      DAT_1fff954b = '\0';
    }
    if (DAT_1fff954c != '\0') {
      DAT_1fff9550 = DAT_1fff9550 | 1;
      DAT_1fff954c = '\0';
    }
  }
  if (((0x14 < DAT_1ffe018d) || (0x14 < DAT_1ffe018e)) && (DAT_1fffab22 == '\0')) {
    DAT_1fffab22 = '\x01';
  }
  return;
}

