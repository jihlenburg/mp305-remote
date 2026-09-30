/* Address: ram:00059ee2; name: FUN_ram_00059ee2; body bytes: 2056 */

/* WARNING: Removing unreachable block (ram,0x0005a452) */
/* WARNING: Removing unreachable block (ram,0x0005a430) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00059ee2(void)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  uint *puVar4;
  uint *puVar5;
  undefined1 uVar6;
  int iVar7;
  undefined4 uVar8;
  byte bVar9;
  short sVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  undefined4 *puVar14;
  int iVar15;
  
  iVar3 = DAT_ram_20001df8;
  gp = 0x20004000;
  iVar15 = DAT_ram_20001df8 + 0x30;
LAB_ram_00059f26:
  do {
    while (puVar4 = DAT_ram_20001eb0, cVar1 = *(char *)(iVar3 + 0xe), cVar1 == -0x3f) {
      if ((*DAT_ram_20001eb0 & 3) != 0) {
        DAT_ram_20001eb0[0x14] = DAT_ram_20001eb0[0x14] & 0xfffffff8;
        *puVar4 = *puVar4 | 8;
      }
      FUN_ram_00059986(iVar3);
      DAT_ram_20001e97 = 0x80;
      DAT_ram_20001e9a = 0;
      DAT_ram_20001e88[0xb] =
           DAT_ram_20001e88[0xb] & 0x81ffffff | (*(byte *)(iVar3 + 0x142) & 0x3f) << 0x19;
      puVar4 = DAT_ram_20001e88;
      DAT_ram_40001040 = 0xa8;
      if (*(byte *)(iVar3 + 0x142) < 0xe) {
        DAT_ram_40001022 = DAT_ram_40001022 & 0xffef;
      }
      else {
        DAT_ram_40001022 = DAT_ram_40001022 | 0x10;
      }
      DAT_ram_20001e88[2] = *(uint *)(iVar3 + 0x98);
      puVar4[1] = *(uint *)(iVar3 + 0x9c);
      puVar5 = DAT_ram_20001eb0;
      DAT_ram_20001eb0[1] = DAT_ram_20001eb0[1] | 1;
      do {
      } while (puVar5[0x19] != 0);
      puVar5[0x19] = 0xa0;
      puVar4[0xb] = puVar4[0xb] & 0xfffffffc | 1;
      if ((*(char *)(iVar3 + 0x15) == '\0') || ((*(byte *)(iVar3 + 0x4a) & 2) == 0)) {
        *puVar4 = *puVar4 & 0xfffffe7f;
        *puVar4 = *puVar4 & 0xfffffe7f | 0x100;
        *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
        puVar5[0x14] = 0xda;
      }
      else {
        iVar7 = FUN_ram_00061b68(1,iVar3);
        puVar4 = DAT_ram_20001e88;
        if (iVar7 != 0) goto LAB_ram_00059ffc;
        *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f;
        *puVar4 = *puVar4 & 0xfffffe7f | 0x100;
        *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
        DAT_ram_20001eb0[0x14] = 0xfa;
      }
      *(uint *)(DAT_ram_20001efc + 0x2c) = *(uint *)(DAT_ram_20001efc + 0x2c) & 0xfffffffd;
      *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xffffff80 | *(byte *)(iVar3 + 0x136) & 0x7f;
      bVar9 = *(byte *)(iVar3 + 0x146);
      *(undefined1 *)(iVar3 + 0xe) = 0xc3;
      DAT_ram_20001e9b = 5;
      sVar10 = *(byte *)(iVar3 + 0x15) + 4;
      if (bVar9 == 2) {
        bVar9 = *(byte *)(iVar3 + 0x148) | 2;
      }
      uVar8 = 0;
LAB_ram_0005a08a:
      FUN_ram_200011be(uVar8,bVar9,sVar10);
    }
    if (cVar1 == -0x3c) {
      if ((DAT_ram_20001e97 & 1) == 0) {
        if (DAT_ram_20001eb0[0x19] != 0) goto LAB_ram_00059f26;
        DAT_ram_20001e98 = 0;
        FUN_ram_00062262();
        if ((char)DAT_ram_20001e97 < '\0') {
          _DAT_ram_20001d72 = _DAT_ram_20001d72 + 1;
        }
        FUN_ram_00056dec(iVar3);
        if (-1 < (char)DAT_ram_20001e97) goto LAB_ram_0005a5a2;
        FUN_ram_00042954();
      }
      else {
        if ((char)DAT_ram_20001e97 < '\0') {
          iVar7 = (uint)(*(byte *)(iVar3 + 0x136) >> 3) + iVar3;
          *(byte *)(iVar7 + 0x130) =
               ~(byte)(1 << (*(byte *)(iVar3 + 0x136) & 7)) & *(byte *)(iVar7 + 0x130);
        }
        if ((*(byte *)(iVar3 + 0xf) & 2) == 0) {
          *(undefined1 *)(iVar3 + 0x1c) = 0x80;
          *(byte *)(iVar3 + 0xf) = *(byte *)(iVar3 + 0xf) | 2;
          DAT_ram_20001dfc = 0;
        }
        DAT_ram_20001e9a =
             FUN_ram_20001120(*(undefined4 *)(iVar3 + 0x114),*(byte *)(iVar3 + 0x4a) & 1,
                              iVar3 + 0x32,iVar15);
        *(char *)(iVar3 + 0x32) = *(char *)(iVar3 + 0x32) - DAT_ram_20001da4._2_1_;
        if ((DAT_ram_20001e9a & 1) == 0) {
          *(undefined1 *)(iVar3 + 0x19) = 0;
          *(undefined2 *)(iVar3 + 0x7e) = 0;
          *(byte *)(iVar3 + 0x29) = *(byte *)(iVar3 + 0x29) | 2;
          iVar7 = FUN_ram_00055dde(iVar3);
          if (iVar7 == 0) {
            iVar7 = *(int *)(iVar3 + 0x118);
            *(undefined1 *)(iVar3 + 0x13) = 0;
            if (((iVar7 != 0) && (*(char *)(iVar3 + 0x1b) != '\0')) &&
               ((*(byte *)(iVar7 + 9) & 1) == 0)) {
              *(ushort *)(iVar7 + 10) = *(ushort *)(iVar7 + 10) | 0xff00;
              FUN_ram_20000104(*(undefined4 *)(iVar7 + 4));
              *(short *)(iVar3 + 0x42) = *(short *)(iVar3 + 0x42) + 1;
              *(undefined4 *)(iVar3 + 0x118) = **(undefined4 **)(iVar3 + 0x118);
              if (*(int *)(iVar3 + 0x188) != 0) {
                *(int *)(iVar3 + 0x188) = *(int *)(iVar3 + 0x188) + -1;
              }
            }
            if ((*(char *)(iVar3 + 0x15) != '\0') && ((*(byte *)(iVar3 + 0x4a) & 2) != 0)) {
              FUN_ram_00055e2e(iVar3);
            }
          }
          if (((DAT_ram_20001e9a & 2) == 0) || ((*(byte *)(iVar3 + 0x4a) & 1) == 0)) {
            iVar7 = FUN_ram_00055e06(iVar3);
            if (iVar7 == 0) {
              FUN_ram_00055d9e(iVar3);
              bVar9 = *(byte *)(iVar3 + 0x11);
              if ((((bVar9 & 8) == 0) || (*(char *)(iVar3 + 0x16) == '\0')) ||
                 ((*(byte *)(iVar3 + 0x17) < 0x12 &&
                  ((0x22064U >> (*(byte *)(iVar3 + 0x17) & 0x1f) & 1) != 0)))) {
                if (*(char *)(iVar3 + 0xd) == '\x03') {
                  if (((0x29 < *(byte *)(iVar3 + 0x17)) ||
                      (iVar7 = (*(code *)(&PTR_LAB_ram_0005b7ec_ram_0006c138)
                                         [*(byte *)(iVar3 + 0x17)])(iVar3), iVar7 != 0)) &&
                     (*(char *)(iVar3 + 0x17) != '\a')) {
                    *(char *)(iVar3 + 0x2c) = *(char *)(iVar3 + 0x17);
                    *(uint *)(iVar3 + 0xa8) = *(uint *)(iVar3 + 0xa8) | 1;
                  }
                }
                else {
                  if (*(char *)(iVar3 + 0x13) == '\0') {
                    cVar1 = *(char *)(iVar3 + 0x10);
                    if (cVar1 == '\x10') {
                      bVar2 = 1;
LAB_ram_0005a39c:
                      *(byte *)(iVar3 + 0x11) = bVar9 | bVar2;
                    }
                    else {
                      if (cVar1 == '\x15') {
                        bVar2 = 2;
                        goto LAB_ram_0005a39c;
                      }
                      if (cVar1 == '\x1c') {
                        *(undefined1 *)(iVar3 + 0x10) = 0;
                        *(uint *)(iVar3 + 0xa0) = *(uint *)(iVar3 + 0xa0) | 1;
                        goto LAB_ram_0005a3ca;
                      }
                      if (cVar1 == 'Y') {
                        bVar2 = *(byte *)(iVar3 + 0x14a);
                        uVar11 = (uint)bVar2;
                        if (((uVar11 == 0) || (uVar11 == 1 << (*(byte *)(iVar3 + 0x146) & 0x1f))) &&
                           ((*(byte *)(iVar3 + 0x14b) == 0 ||
                            ((uint)*(byte *)(iVar3 + 0x14b) ==
                             1 << (*(byte *)(iVar3 + 0x147) & 0x1f))))) {
                          if (*(char *)(iVar3 + 0x1e) != '\0') {
                            *(uint *)(iVar3 + 0xa0) = *(uint *)(iVar3 + 0xa0) | 0x200;
                          }
                        }
                        else {
                          *(byte *)(iVar3 + 0x11) = bVar9 | 0x10;
                        }
                        if (uVar11 != 0) {
                          uVar11 = (uint)*(ushort *)(iVar3 + 0x1ca);
                          if ((bVar2 & 4) == 0) {
                            if ((bVar2 & 1) != 0) {
                              iVar7 = uVar11 - 0x50;
                              goto LAB_ram_0005a438;
                            }
                            iVar7 = uVar11 - 0x44;
                            iVar12 = 4;
                          }
                          else if (*(short *)(iVar3 + 0x148) == 0) {
                            iVar12 = 8;
                            iVar7 = (int)(uVar11 - 0x178) / 8 + -0x2b;
                          }
                          else {
                            iVar7 = (int)(uVar11 - 0x178) / 2 + -0x2b;
LAB_ram_0005a438:
                            iVar12 = 8;
                          }
                          if (iVar12 == 0) {
                            uVar11 = 0xffffffff;
                          }
                          else {
                            uVar11 = iVar7 / iVar12;
                          }
                          uVar13 = (uint)*(ushort *)(iVar3 + 0x1c8);
                          if ((uVar11 & 0xffff) < (uint)*(ushort *)(iVar3 + 0x1c8)) {
                            uVar13 = uVar11 & 0xffff;
                          }
                          *(char *)(iVar3 + 0x4c) = (char)uVar13;
                        }
                      }
                      else if (cVar1 == 'g') {
                        DAT_ram_20001e9e = 0;
                        DAT_ram_20001e88[0x19] = DAT_ram_20001e88[0x19] & 0xfffffffb;
                        DAT_ram_40001018 = (ushort)(((uint)DAT_ram_40001018 << 0x11) >> 0x11);
                        *(byte *)(iVar3 + 0xc) = *(byte *)(iVar3 + 0xc) & 0xdf;
                      }
                      else {
                        if (cVar1 != -0x6b) goto LAB_ram_0005a3ca;
                        *(byte *)(iVar3 + 0x174) = *(byte *)(iVar3 + 0x174) | 4;
                      }
                    }
                    *(undefined1 *)(iVar3 + 0x10) = 1;
                  }
LAB_ram_0005a3ca:
                  if ((*(char *)(iVar3 + 0x16) != '\0') &&
                     (iVar7 = FUN_ram_20000750(iVar3), iVar7 != 0)) goto LAB_ram_0005a1ec;
                }
              }
              else {
                *(undefined1 *)(iVar3 + 0x52) = 0x3d;
                *(undefined1 *)(iVar3 + 0x10) = 0x27;
              }
              if (((*(byte *)(iVar3 + 0x4a) & 1) != 0) && (*(char *)(iVar3 + 0x16) != '\0')) {
                FUN_ram_00055e7e(iVar3);
              }
            }
          }
          else {
            *(char *)(iVar3 + 0x19) = *(char *)(iVar3 + 0x19) + '\x01';
          }
        }
        else {
          *(char *)(iVar3 + 0x18) = *(char *)(iVar3 + 0x18) + '\x01';
          DAT_ram_20001d6e = DAT_ram_20001d6e + 1;
        }
LAB_ram_0005a1ec:
        DAT_ram_20001e97 = 0;
        iVar7 = FUN_ram_2000082c(iVar3);
        if (iVar7 == 1) {
          FUN_ram_00059986(iVar3);
          puVar4 = DAT_ram_20001e88;
          if (((*(byte *)(iVar3 + 0x4a) & 2) == 0) || (*(char *)(iVar3 + 0x15) == '\0')) {
            *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f;
            *puVar4 = *puVar4 & 0xfffffe7f | 0x100;
            *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
            uVar11 = 0xda;
          }
          else {
            iVar7 = FUN_ram_00061b68(1,iVar3);
            puVar4 = DAT_ram_20001e88;
            if (iVar7 != 0) goto LAB_ram_00059ffc;
            *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f;
            *puVar4 = *puVar4 & 0xfffffe7f | 0x100;
            *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
            uVar11 = 0xfa;
          }
          DAT_ram_20001eb0[0x14] = uVar11;
          bVar9 = *(byte *)(iVar3 + 0x146);
          if (bVar9 == 2) {
            bVar9 = *(byte *)(iVar3 + 0x148) | 2;
          }
          FUN_ram_00061f0a(bVar9,*(byte *)(iVar3 + 0x15) + 4);
          puVar4 = DAT_ram_20001e88;
          *DAT_ram_20001e88 = *DAT_ram_20001e88 | 0x800000;
          puVar4[0xb] = puVar4[0xb] & 0xfffffffc;
          *(undefined1 *)(iVar3 + 0xe) = 0xc3;
          iVar7 = *(int *)(iVar3 + 0x120);
          if (((iVar7 != 0) && ((*(byte *)(iVar3 + 0xf) & 1) != 0)) &&
             (iVar7 = thunk_FUN_ram_00052316
                                (*(undefined2 *)(iVar3 + 8),*(undefined1 *)(iVar7 + 8),
                                 *(undefined1 *)(iVar7 + 0xc),*(int *)(iVar7 + 4) + 2), iVar7 == 0))
          {
            puVar14 = *(undefined4 **)(iVar3 + 0x120);
            *(undefined1 *)((int)puVar14 + 9) = 0;
            *(ushort *)((int)puVar14 + 10) = *(ushort *)((int)puVar14 + 10) | 0xff00;
            *(undefined4 *)(iVar3 + 0x120) = *puVar14;
            if (*(short *)(iVar3 + 0x40) != 0) {
              *(short *)(iVar3 + 0x40) = *(short *)(iVar3 + 0x40) + -1;
            }
          }
          bVar9 = *(byte *)(iVar3 + 0x146);
          uVar8 = 2;
          sVar10 = *(byte *)(iVar3 + 0x15) + 4;
          goto LAB_ram_0005a08a;
        }
        FUN_ram_00062262();
        iVar15 = *(int *)(iVar3 + 0x120);
        if (((iVar15 != 0) && ((*(byte *)(iVar3 + 0xf) & 1) != 0)) &&
           (iVar15 = thunk_FUN_ram_00052316
                               (*(undefined2 *)(iVar3 + 8),*(undefined1 *)(iVar15 + 8),
                                *(undefined1 *)(iVar15 + 0xc),*(int *)(iVar15 + 4) + 2), iVar15 == 0
           )) {
          puVar14 = *(undefined4 **)(iVar3 + 0x120);
          *(ushort *)((int)puVar14 + 10) = *(ushort *)((int)puVar14 + 10) | 0xff00;
          *(undefined4 *)(iVar3 + 0x120) = *puVar14;
          if (*(short *)(iVar3 + 0x40) != 0) {
            *(short *)(iVar3 + 0x40) = *(short *)(iVar3 + 0x40) + -1;
          }
        }
        FUN_ram_00056dec(iVar3);
        if (*(byte *)(iVar3 + 0x19) != 0) {
          if ((*(byte *)(iVar3 + 0x19) & 0xf0) != 0) {
            uVar6 = FUN_ram_00056968(iVar3,0x3d);
            *(undefined1 *)(iVar3 + 0x2a) = uVar6;
          }
          if (DAT_ram_20001bec != (code *)0x0) {
            (*DAT_ram_20001bec)(0x86,5);
          }
        }
        if (*(char *)(iVar3 + 0x18) == '\0') goto LAB_ram_0005a5a2;
      }
      if (DAT_ram_20001dac != '\0') {
        FUN_ram_00059856(iVar3);
      }
      goto LAB_ram_0005a5a2;
    }
    if (cVar1 != -0x3d) goto LAB_ram_00059ffc;
    if ((DAT_ram_20001e96 & 1) != 0) {
      DAT_ram_20001e96 = 0;
      if ((*(uint *)(iVar3 + 0xa0) & 1) == 0) {
        FUN_ram_00062030(*(undefined1 *)(iVar3 + 0x147),*(short *)(iVar3 + 0x1c4) + 4,
                         *(undefined2 *)(iVar3 + 0x1c6));
        puVar4 = DAT_ram_20001e88;
        if ((*(byte *)(iVar3 + 0x4a) & 1) == 0) {
          *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f;
          *puVar4 = *puVar4 & 0xfffffe7f | 0x100;
          *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
          uVar11 = 0xd9;
        }
        else {
          FUN_ram_00061bec(0,iVar3);
          puVar4 = DAT_ram_20001e88;
          *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f;
          *puVar4 = *puVar4 & 0xfffffe7f | 0x100;
          *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
          uVar11 = 0xf9;
        }
        sVar10 = *(short *)(iVar3 + 0x1c4);
        DAT_ram_20001eb0[0x14] = uVar11;
        *(undefined1 *)(iVar3 + 0xe) = 0xc4;
        sVar10 = sVar10 + 4;
        bVar9 = *(byte *)(iVar3 + 0x147);
        uVar8 = 1;
        goto LAB_ram_0005a08a;
      }
      FUN_ram_00062262();
      FUN_ram_00042494(*(undefined1 *)(iVar3 + 0x27));
      *(undefined1 *)(iVar3 + 0x27) = 0xff;
      uVar6 = FUN_ram_00056968(iVar3,*(undefined1 *)(iVar3 + 0x52));
      *(undefined1 *)(iVar3 + 0x2a) = uVar6;
      goto LAB_ram_0005a5a2;
    }
    if (DAT_ram_20001eb0[0x19] == 0) {
      DAT_ram_20001e98 = 0;
LAB_ram_00059ffc:
      FUN_ram_00062262();
LAB_ram_0005a5a2:
      FUN_ram_00056878(iVar3);
      return;
    }
  } while( true );
}

