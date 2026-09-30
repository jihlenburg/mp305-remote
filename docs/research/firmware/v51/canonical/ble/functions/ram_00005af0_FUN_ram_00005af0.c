/* Address: ram:00005af0; name: FUN_ram_00005af0; body bytes: 2504 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_ram_00005af0(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5)

{
  byte bVar1;
  short sVar2;
  char *pcVar3;
  char cVar4;
  int iVar5;
  undefined1 *puVar6;
  int iVar7;
  uint extraout_a3;
  uint uVar8;
  undefined2 *puVar9;
  undefined4 uVar10;
  undefined4 extraout_a4;
  undefined1 uVar11;
  ushort uVar12;
  short sVar13;
  char *pcVar14;
  uint uVar15;
  undefined4 uStack_140;
  undefined4 uStack_13c;
  undefined2 uStack_138;
  
  sVar13 = DAT_ram_20002fd8;
  gp = &DAT_ram_20002000;
  if (-1 < (short)param_2) {
    if ((param_2 & 1) != 0) {
      (*_DAT_ram_000401b0)
                (DAT_ram_20002fdc,&PTR_FUN_ram_000056ce_ram_20002e54,
                 &PTR_LAB_ram_000056c0_ram_20002e60,param_4,param_5,_DAT_ram_000401b0);
      (*_DAT_ram_00040058)(DAT_ram_20002fdc,0x20,800);
      (*_DAT_ram_00040058)(DAT_ram_20002fdc,0x400,0x10);
      return param_2 ^ 1;
    }
    if ((param_2 & 0x200) != 0) {
      (*_DAT_ram_0004017c)(0xffff);
      return param_2 ^ 0x200;
    }
    if ((param_2 & 8) != 0) {
      uVar15 = (uint)DAT_ram_20002fd1;
      uVar10 = 2;
      if (uVar15 == 2) {
        if (DAT_ram_20002f36 == -2) goto LAB_ram_0000605c;
        DAT_ram_20004c4c = 0;
        DAT_ram_20002fd3 = '\x01';
        iVar5 = (*_DAT_ram_000400dc)(DAT_ram_20002f36,DAT_ram_20002fdc);
        if (iVar5 == 0) {
          uStack_140 = 0;
          uStack_13c = (undefined1 *)0x0;
          FUN_ram_200028d6(0xb,&LAB_ram_000069fe_2,&uStack_140,8);
          iVar5 = (*_DAT_ram_0004003c)(&DAT_ram_20002f30,(int)&uStack_140 + 1,6);
          if (iVar5 == 0) {
            FUN_ram_200028d6(9,&LAB_ram_000069fe_2,0,8);
            FUN_ram_200028d6(10,&LAB_ram_000069fe_3,&DAT_ram_20002f30,8);
          }
          DAT_ram_20002fc8 = 1;
          goto LAB_ram_0000605c;
        }
        uVar15 = extraout_a3;
        uVar10 = extraout_a4;
        if (iVar5 != 0x16) goto LAB_ram_0000605c;
      }
      else if (DAT_ram_20002f36 == -2) goto LAB_ram_0000605c;
      (*_DAT_ram_00040058)(DAT_ram_20002fdc,8,800,uVar15,uVar10,_DAT_ram_00040058);
LAB_ram_0000605c:
      return param_2 ^ 8;
    }
    if ((param_2 & 0x10) != 0) {
      (*_DAT_ram_00040184)(DAT_ram_20002f36,8,0x28,2,500,_DAT_ram_00040184);
      return param_2 ^ 0x10;
    }
    if ((param_2 & 0x400) != 0) {
      FUN_ram_00003ed6(&DAT_ram_200049b4);
      (*_DAT_ram_00040058)(DAT_ram_20002fdc,0x400,0x10);
      return param_2 ^ 0x400;
    }
    if ((param_2 & 0x20) == 0) {
      if ((param_2 & 0x40) != 0) {
        if (DAT_ram_20002fd8 == 0) {
          uStack_138 = 0;
          uStack_140 = CONCAT22(2,(&DAT_ram_20004c0c)[DAT_ram_20002fd2]);
          uStack_13c = (undefined1 *)
                       (*_DAT_ram_00040128)(DAT_ram_20002f36,0x12,2,0,0,_DAT_ram_00040128);
          if (uStack_13c != (undefined1 *)0x0) {
            *uStack_13c = 1;
            uVar11 = DAT_ram_20002fdc;
            uStack_13c[1] = 0;
            iVar5 = (*_DAT_ram_0004010c)(DAT_ram_20002f36,&uStack_140,uVar11);
            if (iVar5 == 0) {
              DAT_ram_20002fd8 = (short)uStack_140;
              DAT_ram_20002fd2 = 0;
            }
            else {
              (*_DAT_ram_0004012c)(&uStack_140,0x12);
            }
          }
        }
        return param_2 ^ 0x40;
      }
      if ((param_2 & 0x80) != 0) {
        uStack_140 = CONCAT22(uStack_140._2_2_,(&DAT_ram_20004c0c)[DAT_ram_20002fd2]);
        iVar5 = (*_DAT_ram_000400f4)
                          (DAT_ram_20002f36,&uStack_140,DAT_ram_20002fdc,param_4,
                           (uint)DAT_ram_20002fd2 * 2,_DAT_ram_000400f4);
        if (iVar5 == 0) {
          DAT_ram_20002fd8 = (short)uStack_140;
          DAT_ram_20002fd2 = 0;
        }
        return param_2 ^ 0x80;
      }
      if ((param_2 & 0x100) == 0) {
        return 0;
      }
      (*_DAT_ram_00040180)(DAT_ram_20002f36);
      (*_DAT_ram_00040058)(DAT_ram_20002fdc,0x100,0x960);
      return param_2 ^ 0x100;
    }
    if (DAT_ram_20002fd8 == 0) {
      if ((DAT_ram_20004c14 == 0) && (DAT_ram_20002fd6 == '\0')) {
        sVar13 = DAT_ram_20004c4a;
        if (DAT_ram_20004c4a != 0) {
          DAT_ram_20002fd4 = '\x01';
          sVar2 = 0;
          goto LAB_ram_00006124;
        }
      }
      else {
        puVar9 = &DAT_ram_20004c0c;
        iVar5 = 5;
        do {
          if ((puVar9[5] != 0) && ((&DAT_ram_20004c30)[iVar5] == '\0' && DAT_ram_20002fd2 == 0)) {
            DAT_ram_20002fd2 = (byte)iVar5;
            (&DAT_ram_20004c30)[iVar5] = '\x01';
            (*_DAT_ram_00040058)(DAT_ram_20002fdc,0x40,800,0,puVar9,_DAT_ram_00040058);
            break;
          }
          iVar5 = iVar5 + 1;
          puVar9 = puVar9 + 1;
        } while (iVar5 != 0x10);
        sVar2 = DAT_ram_20004c44;
        if ((DAT_ram_20004c2c == 0) || (DAT_ram_20004c40 != '\0' || DAT_ram_20002fd2 != 0)) {
          if ((DAT_ram_20004c0c == 0) || (DAT_ram_20004c30 != '\0' || DAT_ram_20002fd2 != 0)) {
            if (DAT_ram_20004c09 == '\0') goto LAB_ram_000060f4;
            DAT_ram_20004c09 = '\0';
            if (DAT_ram_20004c44 != 0) {
              DAT_ram_20002fd5 = '\x01';
              uVar15 = (uint)DAT_ram_20002fde;
              (&DAT_ram_20004a48)[uVar15] = 0xf0;
              DAT_ram_20002fde = DAT_ram_20002fde + 2;
              (&DAT_ram_20004a48)[uVar15 + 1 & 0xffff] = 0xb0;
              goto LAB_ram_00006124;
            }
            goto LAB_ram_000060f6;
          }
          DAT_ram_20004c30 = '\x01';
        }
        else {
          DAT_ram_20002fd2 = 0x10;
          DAT_ram_20004c40 = '\x01';
        }
        (*_DAT_ram_00040058)(DAT_ram_20002fdc,0x40,800);
      }
      sVar2 = 0;
    }
    else {
LAB_ram_000060f4:
      sVar2 = 0;
LAB_ram_000060f6:
      sVar13 = 0;
    }
LAB_ram_00006124:
    if (DAT_ram_20002fd8 == 0) {
      if (DAT_ram_20002fd5 == '\0') {
        if ((DAT_ram_20002fd4 == '\x01') && (sVar13 != 0)) {
          uStack_140 = CONCAT22(uStack_140._2_2_,sVar13);
          FUN_ram_00007968("ReadcentralCharHdl:%x\n",sVar13);
          iVar5 = (*_DAT_ram_000400f4)(DAT_ram_20002f36,&uStack_140,DAT_ram_20002fdc);
          if (iVar5 == 0) {
            DAT_ram_20002fd4 = '\0';
            DAT_ram_20002fd8 = sVar13;
          }
        }
      }
      else {
        uStack_138 = 0;
        uStack_140 = CONCAT22(DAT_ram_20002fde,sVar2);
        uStack_13c = (undefined1 *)
                     (*_DAT_ram_00040128)
                               (DAT_ram_20002f36,0x12,DAT_ram_20002fde,0,0,_DAT_ram_00040128);
        if (uStack_13c != (undefined1 *)0x0) {
          FUN_ram_000078b2(uStack_13c,&DAT_ram_20004a48,DAT_ram_20002fde);
          iVar5 = (*_DAT_ram_0004010c)(DAT_ram_20002f36,&uStack_140,DAT_ram_20002fdc);
          if (iVar5 == 0) {
            DAT_ram_20002fde = 0;
            DAT_ram_20002fd5 = '\0';
            DAT_ram_20002fd8 = sVar2;
          }
          else {
            (*_DAT_ram_0004012c)(&uStack_140,0x12);
          }
        }
      }
    }
    (*_DAT_ram_00040058)(DAT_ram_20002fdc,0x20,800);
    return param_2 ^ 0x20;
  }
  pcVar3 = (char *)(*_DAT_ram_0004006c)(DAT_ram_20002fdc);
  if (pcVar3 == (char *)0x0) goto LAB_ram_00005b7c;
  if (*pcVar3 == -0x50) {
    cVar4 = pcVar3[4];
    if (DAT_ram_20002fdb == '\x02') {
      if (cVar4 == '\x03') {
LAB_ram_00005bf0:
        DAT_ram_20002fd8 = 0;
        if (cVar4 == '\v') {
LAB_ram_00005bfe:
          for (uVar12 = 0; uVar12 < *(ushort *)(pcVar3 + 8); uVar12 = uVar12 + 1 & 0xff) {
          }
          if ((DAT_ram_20004c4a == DAT_ram_20002fd8) &&
             (DAT_ram_20002fd6 = '\x01', DAT_ram_20004c14 == 0)) {
            FUN_ram_00005864(*(undefined4 *)(pcVar3 + 0xc));
          }
          goto LAB_ram_00005bda;
        }
        if (cVar4 == '\x01') goto LAB_ram_00005bcc;
LAB_ram_00005c3c:
        if (cVar4 == '\x13') goto LAB_ram_00005bda;
        if (cVar4 != '\x1b') goto LAB_ram_00005d64;
        FUN_ram_00001d1a(&uStack_140,0,0x100);
        bVar1 = pcVar3[10];
        uVar8 = (uint)bVar1;
        FUN_ram_00004e1a(*(undefined4 *)(pcVar3 + 0xc),uVar8,0);
        uVar15 = *(ushort *)(pcVar3 + 8) + 1;
        if (DAT_ram_20004c0c == uVar15) {
          DAT_ram_200049b4 = bVar1;
          (*_DAT_ram_0004004c)
                    (&DAT_ram_200049b5,*(undefined4 *)(pcVar3 + 0xc),uVar8,(uint)DAT_ram_20004c0c,
                     uVar15,_DAT_ram_0004004c);
        }
        else if ((DAT_ram_20004c16 <= uVar15) &&
                ((uint)*(ushort *)(pcVar3 + 8) < (uint)DAT_ram_20004c2a)) {
          if (uVar8 < 5) {
            if (uVar8 == 4) {
              uStack_140._0_2_ = CONCAT11(**(undefined1 **)(pcVar3 + 0xc),0xbe);
              uVar11 = (*(undefined1 **)(pcVar3 + 0xc))[3];
              goto LAB_ram_00005d0a;
            }
          }
          else {
            puVar6 = *(undefined1 **)(pcVar3 + 0xc);
            if ((DAT_ram_20002fcd < 2) || (DAT_ram_20002fcc < 5)) {
              uVar11 = *puVar6;
            }
            else {
              uVar11 = puVar6[DAT_ram_20002fcd];
            }
            uStack_140._0_2_ = CONCAT11(uVar11,0xbe);
            if ((DAT_ram_20002fce < 2) || (DAT_ram_20002fcc < 5)) {
              uVar11 = puVar6[uVar8 - 2];
            }
            else {
              uVar11 = puVar6[DAT_ram_20002fce - 1];
            }
LAB_ram_00005d0a:
            uStack_13c = (undefined1 *)CONCAT13(uVar11,(undefined3)uStack_13c);
          }
          if ((DAT_ram_20002fd0 != uStack_140._1_1_) || (uStack_13c._3_1_ != '\0')) {
            DAT_ram_20002fd0 = uStack_140._1_1_;
            FUN_ram_000042a4(&uStack_140,9,0);
          }
        }
      }
      else {
        if (cVar4 != '\x01') {
          if (cVar4 != '\v') goto LAB_ram_00005c3c;
          goto LAB_ram_00005bfe;
        }
        if (pcVar3[8] == '\x02') goto LAB_ram_00005bf0;
LAB_ram_00005bcc:
        if ((pcVar3[8] - 10U & 0xf7) != 0) {
LAB_ram_00005d64:
          if (DAT_ram_20002fd3 != '\0') {
            if (DAT_ram_20002fd3 == '\x01') {
              if (cVar4 == '\x11') {
                if (pcVar3[1] == '\x1a') {
LAB_ram_00005d86:
                  DAT_ram_20002fd3 = '\x02';
                  (*_DAT_ram_000400e8)
                            (DAT_ram_20002f36,1,0xffff,DAT_ram_20002fdc,&DAT_ram_20002d88,
                             _DAT_ram_000400e8);
                }
              }
              else if (cVar4 == '\x01') goto LAB_ram_00005d86;
            }
            else if (((DAT_ram_20002fd3 == '\x02') && (cVar4 == '\t')) &&
                    (*(short *)(pcVar3 + 8) != 0)) {
              FUN_ram_00007ab4("TypeRspAnalysis");
              DAT_ram_20002fd8 = 1;
              for (uVar15 = 0; uVar15 < *(ushort *)(pcVar3 + 8); uVar15 = uVar15 + 1 & 0xff) {
                uVar12 = *(ushort *)(pcVar3 + 10);
                iVar7 = uVar12 * uVar15;
                iVar5 = *(int *)(pcVar3 + 0xc) + iVar7;
                bVar1 = *(byte *)(iVar5 + 2);
                sVar13 = *(short *)(iVar5 + 3);
                pcVar14 = (char *)(*(int *)(pcVar3 + 0xc) + iVar7 + 5);
                for (uVar8 = 0; (uVar8 & 0xff) < (uVar12 - 5 & 0xff); uVar8 = uVar8 + 1) {
                  FUN_ram_00007968("%02x ",pcVar14[uVar8]);
                }
                FUN_ram_000079ac(10);
                if ((((bVar1 & 2) != 0) && (*pcVar14 == 'K')) && (pcVar14[1] == '*')) {
                  DAT_ram_20004c4a = sVar13;
                }
                if ((((bVar1 & 0xc) != 0) && (DAT_ram_20004c4c = sVar13, *pcVar14 == '\x02')) &&
                   (pcVar14[1] == -0x51)) {
                  DAT_ram_20004c44 = sVar13;
                }
                if ((bVar1 & 0x10) != 0) {
                  DAT_ram_20004c2c = sVar13 + 1;
                }
                if ((bVar1 & 0x20) != 0) {
                  DAT_ram_20004c2c = sVar13 + 1;
                }
                if ((*pcVar14 == 'N') && (pcVar14[1] == '*')) {
                  DAT_ram_20004c48 = sVar13;
                }
                if (*pcVar14 == 'M') {
                  if ((pcVar14[1] == '*') && ((bVar1 & 0x10) != 0)) {
                    puVar9 = &DAT_ram_20004c0c;
                    iVar5 = 5;
                    do {
                      if (puVar9[5] == 0) {
                        DAT_ram_20004c2a = sVar13 + 1;
                        (&DAT_ram_20004c0c)[iVar5] = DAT_ram_20004c2a;
                        break;
                      }
                      iVar5 = iVar5 + 1;
                      puVar9 = puVar9 + 1;
                    } while (iVar5 != 0x10);
                  }
                }
                else if (((*pcVar14 == '\x02') && (pcVar14[1] == -0x51)) && ((bVar1 & 0x10) != 0)) {
                  DAT_ram_20004c0c = sVar13 + 1;
                }
              }
              goto LAB_ram_00005bda;
            }
          }
          goto LAB_ram_00005be2;
        }
LAB_ram_00005bda:
        DAT_ram_20002fd8 = 0;
      }
LAB_ram_00005be2:
      cVar4 = pcVar3[4];
    }
    (*_DAT_ram_0004012c)(pcVar3 + 8,cVar4);
  }
  (*_DAT_ram_00040068)(pcVar3);
LAB_ram_00005b7c:
  return param_2 ^ 0x8000;
}

