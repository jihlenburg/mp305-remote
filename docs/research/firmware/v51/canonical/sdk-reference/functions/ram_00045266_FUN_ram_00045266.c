/* Address: ram:00045266; name: FUN_ram_00045266; body bytes: 1572 */

/* WARNING: Restarted to delay deadcode elimination for space: ram */

uint FUN_ram_00045266(undefined4 param_1,uint param_2)

{
  char cVar1;
  byte bVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  char cVar7;
  char *pcVar8;
  uint uVar9;
  int iVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  char *pcVar13;
  code *pcVar14;
  char cVar15;
  ushort uStack_4a;
  ushort auStack_48 [10];
  
  gp = 0x20004000;
  if ((short)param_2 < 0) {
    pcVar8 = (char *)tmos_msg_receive(DAT_ram_20001d4c);
    while (cVar15 = DAT_ram_20001d4e, cVar7 = DAT_ram_20001c07, pcVar8 != (char *)0x0) {
      if (*pcVar8 == -0x5e) {
        uVar3 = *(undefined2 *)(pcVar8 + 2);
        uVar12 = 0xffff;
        cVar15 = DAT_ram_20001c07;
LAB_ram_000452f6:
        iVar10 = FUN_ram_00044406(uVar3,uVar12,pcVar8);
LAB_ram_0004545c:
        if (iVar10 == 0) goto LAB_ram_00045474;
        goto LAB_ram_0004531e;
      }
      if (*pcVar8 != -0x6f) goto LAB_ram_00045474;
      cVar1 = pcVar8[1];
      if (cVar1 == '\x05') {
        FUN_ram_00044452(pcVar8);
        goto LAB_ram_0004531e;
      }
      if (cVar1 == '\x0e') {
        uVar9 = (uint)*(ushort *)(pcVar8 + 4);
        if (uVar9 == 0x1009) {
          cVar7 = **(char **)(pcVar8 + 8);
          if ((cVar7 == '\0') && (pcVar13 = *(char **)(pcVar8 + 8) + 1, pcVar13 != (char *)0x0)) {
            tmos_memcpy(&DAT_ram_20001c1c,pcVar13,6);
          }
          if (DAT_ram_20001c04 == '\x01') {
            if (cVar7 == '\0') {
              DAT_ram_20001c04 = '\x02';
              thunk_FUN_ram_00065204();
            }
            else {
              DAT_ram_20001c04 = '\0';
LAB_ram_00045378:
              FUN_ram_00044794(cVar7);
            }
            goto LAB_ram_0004531e;
          }
        }
        else {
          if (uVar9 != 0x2002) {
            if (uVar9 == 0x2005) {
              FUN_ram_00044a2c(**(undefined1 **)(pcVar8 + 8));
              goto LAB_ram_0004531e;
            }
            if ((uVar9 - 0x2006 & 0xffff) < 5) {
LAB_ram_0004544a:
              if ((DAT_ram_200019f0 != (undefined4 *)0x0) &&
                 ((code *)*DAT_ram_200019f0 != (code *)0x0)) {
                iVar10 = (*(code *)*DAT_ram_200019f0)(pcVar8);
                goto LAB_ram_0004545c;
              }
              goto LAB_ram_0004531e;
            }
            if ((uVar9 - 0x2036 & 0xffff) < 0x1d) {
              if ((0x1800070fU >> (uVar9 - 0x2036 & 0x1f) & 1) != 0) goto LAB_ram_0004544a;
LAB_ram_00045498:
              if (uVar9 != 0x2041) goto LAB_ram_00045474;
            }
            else if (uVar9 != 0x200b) {
              if (uVar9 == 0x200c) {
                if (**(char **)(pcVar8 + 8) != '\0') goto LAB_ram_00045474;
                goto LAB_ram_0004531e;
              }
              if (uVar9 == 0x200e) goto LAB_ram_0004548c;
              goto LAB_ram_00045498;
            }
            if (DAT_ram_200019e8 == (int *)0x0) goto LAB_ram_0004531e;
            pcVar14 = (code *)*DAT_ram_200019e8;
LAB_ram_00045430:
            if (pcVar14 != (code *)0x0) {
LAB_ram_00045436:
              iVar10 = (*pcVar14)(uVar9,pcVar8);
              goto LAB_ram_0004545c;
            }
            goto LAB_ram_0004531e;
          }
          pcVar13 = *(char **)(pcVar8 + 8);
          if (pcVar13 != (char *)0x0) {
            if (*pcVar13 == '\0') {
              DAT_ram_20001c0c = *(undefined2 *)(pcVar13 + 1);
              DAT_ram_20001c05 = pcVar13[3];
            }
            if (DAT_ram_20001c04 == '\x02') {
              if (*pcVar13 == '\0') {
                DAT_ram_20001c04 = '\x03';
                FUN_ram_0004c83e(DAT_ram_20001c0c,DAT_ram_20001c05);
              }
              else {
                DAT_ram_20001c04 = '\0';
              }
              cVar7 = *pcVar13;
              goto LAB_ram_00045378;
            }
          }
        }
LAB_ram_00045474:
        if (cVar15 == -1) goto LAB_ram_0004531e;
        tmos_msg_send(cVar15,pcVar8);
      }
      else {
        if (cVar1 != '\x0f') {
          if (cVar1 != '>') goto LAB_ram_00045474;
          cVar1 = pcVar8[2];
          if (cVar1 == '\x01') {
            if (pcVar8[6] == '\0') {
              if (DAT_ram_200019e0 != (char *)0x0) {
                cVar7 = *DAT_ram_200019e0;
              }
              uVar12 = 8;
            }
            else {
              uVar12 = 4;
              if ((DAT_ram_200019f0 != (undefined4 *)0x0) &&
                 (uVar12 = 4, (code *)DAT_ram_200019f0[1] != (code *)0x0)) {
                (*(code *)DAT_ram_200019f0[1])(0,0);
              }
            }
            uVar11 = FUN_ram_00044326(pcVar8[7],pcVar8 + 8);
            pcVar8[7] = (char)uVar11;
            FUN_ram_0004491e(pcVar8[3],cVar7,uVar11,pcVar8 + 8,*(undefined2 *)(pcVar8 + 4),uVar12,
                             *(undefined2 *)(pcVar8 + 0xe),*(undefined2 *)(pcVar8 + 0x10),
                             *(undefined2 *)(pcVar8 + 0x12),pcVar8[0x14]);
            if (pcVar8[3] == '\0') {
              uVar3 = *(undefined2 *)(pcVar8 + 0x10);
              uVar4 = *(undefined2 *)(pcVar8 + 0xe);
              cVar15 = pcVar8[7];
              uVar5 = *(undefined2 *)(pcVar8 + 4);
              uVar6 = *(undefined2 *)(pcVar8 + 0x12);
LAB_ram_0004557c:
              cVar7 = FUN_ram_0004e2a2(cVar7,uVar5,1,cVar15,pcVar8 + 8,uVar12,uVar4,uVar3,uVar6,0x17
                                      );
              pcVar8[3] = cVar7;
            }
          }
          else {
            if (cVar1 != '\n') {
              if (cVar1 == '\x02') {
                if (DAT_ram_200019e8 != (int *)0x0) {
                  pcVar14 = (code *)DAT_ram_200019e8[1];
LAB_ram_000456a8:
                  if (pcVar14 != (code *)0x0) {
                    (*pcVar14)(pcVar8);
                  }
                }
              }
              else if (cVar1 == '\v') {
                if (DAT_ram_200019e8 != (int *)0x0) {
                  pcVar14 = (code *)DAT_ram_200019e8[2];
                  goto LAB_ram_000456a8;
                }
              }
              else {
                if (cVar1 == '\x03') {
                  uVar12 = 3;
LAB_ram_000456ce:
                  uVar3 = *(undefined2 *)(pcVar8 + 4);
                  goto LAB_ram_000452f6;
                }
                if (cVar1 == '\x06') {
                  GAPRole_GetParameter(0x311,&uStack_4a);
                  GAPRole_GetParameter(0x312,auStack_48);
                  if ((auStack_48[0] < *(ushort *)(pcVar8 + 6)) ||
                     (*(ushort *)(pcVar8 + 8) < uStack_4a)) {
                    thunk_FUN_ram_000656a8(*(undefined2 *)(pcVar8 + 4),0x20);
                  }
                  else {
                    if (*(ushort *)(pcVar8 + 6) < uStack_4a) {
                      *(ushort *)(pcVar8 + 6) = uStack_4a;
                    }
                    if (auStack_48[0] < *(ushort *)(pcVar8 + 8)) {
                      *(ushort *)(pcVar8 + 8) = auStack_48[0];
                    }
                    thunk_FUN_ram_00065676
                              (*(undefined2 *)(pcVar8 + 4),*(undefined2 *)(pcVar8 + 6),
                               *(undefined2 *)(pcVar8 + 8),*(undefined2 *)(pcVar8 + 10),
                               *(undefined2 *)(pcVar8 + 0xc),0,0);
                  }
                }
                else {
                  if (cVar1 == '\a') goto LAB_ram_00045474;
                  if (cVar1 == '\f') {
                    uVar12 = 0xc;
                    goto LAB_ram_000456ce;
                  }
                  if (cVar1 == '\r') {
                    if (DAT_ram_200019e8 != (int *)0x0) {
                      pcVar14 = (code *)DAT_ram_200019e8[3];
                      goto LAB_ram_000456a8;
                    }
                  }
                  else if (cVar1 == '\x0e') {
                    FUN_ram_00045fea(pcVar8);
                  }
                  else if (cVar1 == '\x0f') {
                    if (DAT_ram_200019e8 != (int *)0x0) {
                      pcVar14 = (code *)DAT_ram_200019e8[4];
                      goto LAB_ram_000456a8;
                    }
                  }
                  else if (cVar1 == '\x10') {
                    FUN_ram_0004609c(pcVar8);
                  }
                  else {
                    if (cVar1 != '\x11') {
                      if (cVar1 == '\x12') {
                        if ((DAT_ram_200019f0 != (undefined4 *)0x0) &&
                           (pcVar14 = (code *)DAT_ram_200019f0[1], pcVar14 != (code *)0x0)) {
                          uVar12 = 1;
                          pcVar13 = (char *)0x0;
LAB_ram_000457b8:
                          (*pcVar14)(uVar12,pcVar13);
                        }
                      }
                      else if (cVar1 == '\x13') {
                        if ((DAT_ram_200019f0 != (undefined4 *)0x0) &&
                           (pcVar14 = (code *)DAT_ram_200019f0[1], pcVar14 != (code *)0x0)) {
                          uVar12 = 2;
                          pcVar13 = pcVar8;
                          goto LAB_ram_000457b8;
                        }
                      }
                      else if (cVar1 == '\x18') {
                        uVar12 = 0x18;
                        goto LAB_ram_000456ce;
                      }
                      goto LAB_ram_00045474;
                    }
                    FUN_ram_000461a2(0);
                  }
                }
              }
              goto LAB_ram_0004531e;
            }
            if (pcVar8[6] == '\0') {
              if (DAT_ram_200019e0 != (char *)0x0) {
                cVar7 = *DAT_ram_200019e0;
              }
              uVar12 = 8;
            }
            else {
              uVar12 = 4;
              if ((DAT_ram_200019f0 != (undefined4 *)0x0) &&
                 (uVar12 = 4, (code *)DAT_ram_200019f0[1] != (code *)0x0)) {
                (*(code *)DAT_ram_200019f0[1])(0,0);
              }
            }
            bVar2 = pcVar8[7];
            uVar9 = bVar2 & 1;
            if ((bVar2 & 2) == 0) {
              uVar9 = FUN_ram_00044326((uint)bVar2,pcVar8 + 8);
            }
            pcVar8[7] = (char)uVar9;
            FUN_ram_0004491e(pcVar8[3],cVar7,uVar9,pcVar8 + 8,*(undefined2 *)(pcVar8 + 4),uVar12,
                             *(undefined2 *)(pcVar8 + 0x1a),*(undefined2 *)(pcVar8 + 0x1c),
                             *(undefined2 *)(pcVar8 + 0x1e),pcVar8[0x20]);
            if (pcVar8[3] == '\0') {
              uVar3 = *(undefined2 *)(pcVar8 + 0x1c);
              uVar4 = *(undefined2 *)(pcVar8 + 0x1a);
              cVar15 = pcVar8[7];
              uVar5 = *(undefined2 *)(pcVar8 + 4);
              uVar6 = *(undefined2 *)(pcVar8 + 0x1e);
              goto LAB_ram_0004557c;
            }
          }
          if (DAT_ram_200019e0 != (char *)0x0) {
            FUN_ram_00044f96(4);
          }
          if ((DAT_ram_20001a00 != '\0') &&
             (iVar10 = FUN_ram_00043e98(DAT_ram_20001a00,DAT_ram_20001a01), iVar10 != 0)) {
            cVar7 = pcVar8[3];
            if (cVar7 != '1') {
              FUN_ram_0004403a(cVar7,DAT_ram_20001a00,*(undefined2 *)(pcVar8 + 4),cVar7,uVar12);
            }
            DAT_ram_20001a00 = '\0';
          }
          goto LAB_ram_0004531e;
        }
        uVar9 = (uint)*(ushort *)(pcVar8 + 4);
        if ((uVar9 == 0x200d) || (uVar9 == 0x2019)) {
LAB_ram_0004548c:
          if (DAT_ram_200019ec == 0) goto LAB_ram_0004531e;
          pcVar14 = *(code **)(DAT_ram_200019ec + 4);
          goto LAB_ram_00045430;
        }
        if (uVar9 != 0x2013) goto LAB_ram_00045474;
        if (DAT_ram_20001c0a == -1) {
          if (DAT_ram_200019ec != 0) {
            pcVar14 = *(code **)(DAT_ram_200019ec + 4);
LAB_ram_000454dc:
            if (pcVar14 != (code *)0x0) {
              uVar9 = 0x2013;
              goto LAB_ram_00045436;
            }
          }
        }
        else if (DAT_ram_200019f4 != (undefined4 *)0x0) {
          pcVar14 = (code *)*DAT_ram_200019f4;
          goto LAB_ram_000454dc;
        }
LAB_ram_0004531e:
        tmos_msg_deallocate(pcVar8);
      }
      pcVar8 = (char *)tmos_msg_receive(DAT_ram_20001d4c);
    }
    uVar9 = param_2 ^ 0x8000;
  }
  else if ((param_2 & 1) == 0) {
    if ((param_2 & 2) == 0) {
      uVar9 = 0;
      if ((param_2 & 4) != 0) {
        if (((DAT_ram_200019e4 != 0) &&
            (DAT_ram_20001c08 = 1, DAT_ram_200019f0 != (undefined4 *)0x0)) &&
           ((code *)DAT_ram_200019f0[1] != (code *)0x0)) {
          (*(code *)DAT_ram_200019f0[1])(1,0);
        }
        FUN_ram_0004eef8(DAT_ram_20001c10,auStack_48);
        FUN_ram_000449da(auStack_48);
        if (DAT_ram_20001c46 != 0) {
          tmos_start_task(DAT_ram_20001d4c,4,(uint)DAT_ram_20001c46 * 0x640);
        }
        uVar9 = param_2 ^ 4;
      }
    }
    else {
      if ((DAT_ram_200019f0 != (undefined4 *)0x0) && ((code *)DAT_ram_200019f0[1] != (code *)0x0)) {
        (*(code *)DAT_ram_200019f0[1])(1,0);
      }
      uVar9 = param_2 ^ 2;
    }
  }
  else {
    if ((DAT_ram_200019e8 != (int *)0x0) && ((code *)DAT_ram_200019e8[1] != (code *)0x0)) {
      (*(code *)DAT_ram_200019e8[1])(0);
    }
    uVar9 = param_2 ^ 1;
  }
  return uVar9;
}

