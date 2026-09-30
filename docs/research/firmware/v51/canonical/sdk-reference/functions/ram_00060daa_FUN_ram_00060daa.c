/* Address: ram:00060daa; name: FUN_ram_00060daa; body bytes: 2546 */

/* WARNING: Removing unreachable block (ram,0x000615a8) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00060daa(void)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  uint *puVar4;
  uint *puVar5;
  uint uVar6;
  byte bVar7;
  undefined1 uVar8;
  uint uVar9;
  short sVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  undefined4 *puVar14;
  int iVar15;
  uint uStack_38;
  uint uStack_34;
  
  iVar3 = DAT_ram_20001df8;
  gp = 0x20004000;
LAB_ram_00060df4:
  do {
    while (puVar4 = DAT_ram_20001eb0, cVar1 = *(char *)(iVar3 + 0xe), cVar1 == -0x30) {
      if ((*DAT_ram_20001eb0 & 3) != 0) {
        DAT_ram_20001eb0[0x14] = DAT_ram_20001eb0[0x14] & 0xfffffff8;
        *puVar4 = *puVar4 | 8;
      }
      if ((*(byte *)(iVar3 + 0x4a) & 1) != 0) {
        FUN_ram_00061bec(1,iVar3);
      }
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
      puVar4 = DAT_ram_20001eb0;
      DAT_ram_20001eb0[1] = DAT_ram_20001eb0[1] | 1;
      DAT_ram_20001e9b = 5;
      *(undefined1 *)(iVar3 + 0xe) = 0xd1;
      DAT_ram_20001e94 = 0xc0;
      do {
      } while (puVar4[0x19] != 0);
      FUN_ram_00062030(*(undefined1 *)(iVar3 + 0x147),*(short *)(iVar3 + 0x1c4) + 4,
                       *(undefined2 *)(iVar3 + 0x1c6));
      cVar1 = *(char *)(iVar3 + 0x147);
      uVar11 = (uint)*(ushort *)(iVar3 + 0x80);
      uVar2 = *(ushort *)(iVar3 + 0x84);
      if (cVar1 == '\x02') {
        DAT_ram_20001eb0[3] = 0xd00f;
        puVar4 = DAT_ram_20001eb0;
        fence.i();
        DAT_ram_20001eb0[2] = 0x2000;
        DAT_ram_20001e98 = 0x80;
        puVar4[0x19] = (uVar11 + 0x189 + (uint)uVar2 * 2) * 2;
        puVar4[3] = 0xf00f;
      }
      else {
        DAT_ram_20001eb0[3] = 0xd00f;
        puVar4 = DAT_ram_20001eb0;
        if (cVar1 == '\x01') {
          fence.i();
          iVar12 = uVar11 + 0x35;
          DAT_ram_20001eb0[2] = 0x2000;
        }
        else {
          fence.i();
          iVar12 = uVar11 + 0x49;
          DAT_ram_20001eb0[2] = 0x2000;
        }
        DAT_ram_20001e98 = 0x80;
        puVar4[0x19] = (iVar12 + (uint)uVar2 * 2) * 2;
        puVar4[3] = 0xf00f;
      }
      puVar5 = DAT_ram_20001eb0;
      DAT_ram_20001e99 = 0;
      DAT_ram_20001e95 = 0;
      *DAT_ram_20001eb0 = 1;
      iVar12 = DAT_ram_20001efc;
      puVar4 = DAT_ram_20001e88;
      if ((*(byte *)(iVar3 + 0x4a) & 1) == 0) {
        *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f;
        *puVar4 = *puVar4 & 0xfffffe7f | 0x100;
        *(uint *)(iVar12 + 8) = *(uint *)(iVar12 + 8) | 0x330000;
        uVar11 = 0xd9;
      }
      else {
        *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f;
        *puVar4 = *puVar4 & 0xfffffe7f | 0x100;
        *(uint *)(iVar12 + 8) = *(uint *)(iVar12 + 8) | 0x330000;
        uVar11 = 0xf9;
      }
      puVar5[0x14] = uVar11;
      *(uint *)(iVar12 + 0x2c) = *(uint *)(iVar12 + 0x2c) & 0xfffffffd;
      *puVar4 = *puVar4 & 0xffffff80 | *(byte *)(iVar3 + 0x136) & 0x7f;
LAB_ram_00060f76:
      FUN_ram_200010ec();
    }
    if (cVar1 == -0x2f) {
      if ((DAT_ram_20001e94 & 1) != 0) {
        if ((char)DAT_ram_20001e94 < '\0') {
          if ((*(byte *)(iVar3 + 0xf) & 0x20) != 0) {
            if (*(uint *)(iVar3 + 0x94) == 0) {
              sVar10 = -1;
            }
            else {
              sVar10 = (short)(((uint)*(ushort *)(iVar3 + 0x38) * 0x4e2) / *(uint *)(iVar3 + 0x94));
            }
            *(ushort *)(iVar3 + 0x82) = sVar10 + DAT_ram_20001bd4 + 0x50;
          }
          cVar1 = DAT_ram_20001bd2;
          iVar12 = DAT_ram_20001ea4 + *(int *)(iVar3 + 0x8c);
          if ((*DAT_ram_20001e88 >> 0xc & 3) == 2) {
            iVar13 = *(ushort *)(iVar3 + 0x82) + 0x189;
          }
          else {
            iVar13 = *(ushort *)(iVar3 + 0x82) + 0x49;
          }
          iVar13 = FUN_ram_0006bae2((uint)DAT_ram_20001b8c * iVar13,
                                    (int)((longlong)iVar13 * (ulonglong)(uint)DAT_ram_20001b8c >>
                                         0x20),1000000,0);
          uVar11 = iVar12 - iVar13;
          if ((-1 < cVar1) && (0xa8bfffff < uVar11)) {
            uVar11 = uVar11 + 0x57400000;
          }
          *(uint *)(iVar3 + 0x90) = uVar11;
          *(undefined2 *)(iVar3 + 0x7e) = 0;
          *(ushort *)(iVar3 + 0x84) = *(ushort *)(iVar3 + 0x84) >> 1;
        }
        DAT_ram_20001e9a =
             FUN_ram_20001120(*(undefined4 *)(iVar3 + 0x114),*(byte *)(iVar3 + 0x4a) & 1,
                              iVar3 + 0x32,iVar3 + 0x30);
        *(char *)(iVar3 + 0x32) = *(char *)(iVar3 + 0x32) - DAT_ram_20001da4._2_1_;
        if ((DAT_ram_20001e9a & 1) == 0) {
          *(byte *)(iVar3 + 0x29) = *(byte *)(iVar3 + 0x29) | 2;
          if ((char)DAT_ram_20001e94 < '\0') {
            iVar12 = (uint)(*(byte *)(iVar3 + 0x136) >> 3) + iVar3;
            *(byte *)(iVar12 + 0x130) =
                 ~(byte)(1 << (*(byte *)(iVar3 + 0x136) & 7)) & *(byte *)(iVar12 + 0x130);
          }
          if (((*(byte *)(iVar3 + 0xf) & 2) != 0) && (iVar12 = FUN_ram_00055dde(iVar3), iVar12 == 0)
             ) {
            *(undefined1 *)(iVar3 + 0x13) = 0;
            *(byte *)(iVar3 + 0xf) = *(byte *)(iVar3 + 0xf) | 4;
            iVar12 = *(int *)(iVar3 + 0x118);
            if ((iVar12 != 0) &&
               ((*(char *)(iVar3 + 0x1b) != '\0' && ((*(byte *)(iVar12 + 9) & 1) == 0)))) {
              *(ushort *)(iVar12 + 10) = *(ushort *)(iVar12 + 10) | 0xff00;
              FUN_ram_20000104(*(undefined4 *)(iVar12 + 4));
              *(short *)(iVar3 + 0x42) = *(short *)(iVar3 + 0x42) + 1;
              *(undefined4 *)(iVar3 + 0x118) = **(undefined4 **)(iVar3 + 0x118);
            }
            if ((*(char *)(iVar3 + 0x15) != '\0') && ((*(byte *)(iVar3 + 0x4a) & 2) != 0)) {
              FUN_ram_00055e2e(iVar3);
            }
            cVar1 = *(char *)(iVar3 + 0x10);
            if (cVar1 == '\"') {
              *(undefined1 *)(iVar3 + 0x2a) = 0;
              *(uint *)(iVar3 + 0xa0) = *(uint *)(iVar3 + 0xa0) | 8;
              *(byte *)(iVar3 + 0x11) = *(byte *)(iVar3 + 0x11) | 8;
              uVar8 = 0x24;
LAB_ram_000611ca:
              *(undefined1 *)(iVar3 + 0x10) = uVar8;
            }
            else if (cVar1 == '`') {
              *(undefined1 *)(iVar3 + 0x10) = 1;
              *(byte *)(iVar3 + 0x29) = *(byte *)(iVar3 + 0x29) | 1;
            }
            else {
              if (cVar1 == 'g') {
                DAT_ram_20001e9e = 0;
                DAT_ram_20001e88[0x19] = DAT_ram_20001e88[0x19] & 0xfffffffb;
                DAT_ram_40001018 = (ushort)(((uint)DAT_ram_40001018 << 0x11) >> 0x11);
                *(byte *)(iVar3 + 0xc) = *(byte *)(iVar3 + 0xc) & 0xdf;
                uVar8 = 1;
                goto LAB_ram_000611ca;
              }
              if (cVar1 == '\x1c') {
                *(uint *)(iVar3 + 0xa0) = *(uint *)(iVar3 + 0xa0) | 1;
              }
            }
          }
          if (((DAT_ram_20001e9a & 2) == 0) || ((*(byte *)(iVar3 + 0x4a) & 1) == 0)) {
            iVar12 = FUN_ram_00055e06(iVar3);
            if (iVar12 == 0) {
              *(undefined1 *)(iVar3 + 0x19) = 0;
              FUN_ram_00055d9e(iVar3);
              if ((((*(byte *)(iVar3 + 0x11) & 8) == 0) || (*(char *)(iVar3 + 0x16) == '\0')) ||
                 ((*(byte *)(iVar3 + 0x17) & 0xfb) == 2)) {
                if (*(char *)(iVar3 + 0xd) == '\x03') {
                  if (((0x28 < *(byte *)(iVar3 + 0x17)) ||
                      (iVar12 = (*(code *)(&PTR_LAB_ram_0005b7ec_ram_0006c138)
                                          [*(byte *)(iVar3 + 0x17)])(iVar3), iVar12 != 0)) &&
                     (*(char *)(iVar3 + 0x17) != '\a')) {
                    *(char *)(iVar3 + 0x2c) = *(char *)(iVar3 + 0x17);
                    *(uint *)(iVar3 + 0xa8) = *(uint *)(iVar3 + 0xa8) | 1;
                    FUN_ram_0005ac30(iVar3);
                  }
                }
                else if ((*(char *)(iVar3 + 0x16) == '\0') ||
                        (iVar12 = FUN_ram_20000750(iVar3), iVar12 != 0)) goto LAB_ram_0006120e;
                if (*(char *)(iVar3 + 0x16) == '\0') goto LAB_ram_0006120e;
              }
              else {
                *(undefined1 *)(iVar3 + 0x52) = 0x3d;
                *(undefined1 *)(iVar3 + 0x10) = 0x27;
              }
              if ((*(byte *)(iVar3 + 0x4a) & 1) != 0) {
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
LAB_ram_0006120e:
        if ((*(byte *)(iVar3 + 0xf) & 2) == 0) {
          *(byte *)(iVar3 + 0xf) = *(byte *)(iVar3 + 0xf) | 2;
          *(undefined1 *)(iVar3 + 0x1c) = 0x80;
          if (*(uint *)(iVar3 + 0x94) == 0) {
            uVar11 = 0xffffffff;
          }
          else {
            uVar11 = ((uint)*(ushort *)(iVar3 + 0x38) * 0x4e2) / *(uint *)(iVar3 + 0x94);
          }
          uVar11 = uVar11 + DAT_ram_20001bd4 + 0x50;
          *(short *)(iVar3 + 0x82) = (short)(uVar11 * 0x10000 >> 0x10);
          *(short *)(iVar3 + 0x80) = (short)((uVar11 & 0xffff) << 1);
          DAT_ram_20001dfc = 0;
        }
        DAT_ram_20001e94 = 0;
        FUN_ram_000607c0(iVar3);
        bVar7 = *(byte *)(iVar3 + 0x146);
        if (bVar7 == 2) {
          bVar7 = *(byte *)(iVar3 + 0x148) | 2;
        }
        FUN_ram_00061f0a(bVar7,*(byte *)(iVar3 + 0x15) + 4);
        puVar4 = DAT_ram_20001e88;
        if ((*(char *)(iVar3 + 0x15) == '\0') || ((*(byte *)(iVar3 + 0x4a) & 2) == 0)) {
          *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f;
          *puVar4 = *puVar4 & 0xfffffe7f | 0x100;
          *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
          uVar11 = 0xda;
        }
        else {
          iVar12 = FUN_ram_00061b68(0,iVar3);
          puVar4 = DAT_ram_20001e88;
          if (iVar12 != 0) goto LAB_ram_0006129c;
          *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f;
          *puVar4 = *puVar4 & 0xfffffe7f | 0x100;
          *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
          uVar11 = 0xfa;
        }
        DAT_ram_20001eb0[0x14] = uVar11;
        puVar4 = DAT_ram_20001e88;
        *DAT_ram_20001e88 = *DAT_ram_20001e88 | 0x800000;
        puVar4[0xb] = puVar4[0xb] & 0xfffffffc;
        *(undefined1 *)(iVar3 + 0xe) = 0xd2;
        iVar12 = *(int *)(iVar3 + 0x120);
        if (((iVar12 != 0) && ((*(byte *)(iVar3 + 0xf) & 1) != 0)) &&
           (iVar12 = thunk_FUN_ram_00052316
                               (*(undefined2 *)(iVar3 + 8),*(undefined1 *)(iVar12 + 8),
                                *(undefined1 *)(iVar12 + 0xc),*(int *)(iVar12 + 4) + 2), iVar12 == 0
           )) {
          puVar14 = *(undefined4 **)(iVar3 + 0x120);
          *(ushort *)((int)puVar14 + 10) = *(ushort *)((int)puVar14 + 10) | 0xff00;
          *(undefined4 *)(iVar3 + 0x120) = *puVar14;
          if (*(short *)(iVar3 + 0x40) != 0) {
            *(short *)(iVar3 + 0x40) = *(short *)(iVar3 + 0x40) + -1;
          }
        }
        goto LAB_ram_00060f76;
      }
      if (DAT_ram_20001eb0[0x19] == 0) {
        DAT_ram_20001e98 = 0;
        FUN_ram_00062262();
        if ((char)DAT_ram_20001e94 < '\0') {
          FUN_ram_000607a4();
          _DAT_ram_20001d70 = CONCAT22(_DAT_ram_20001d72 + 1,DAT_ram_20001d70);
          if ((*(byte *)(iVar3 + 0x174) & 1) != 0) {
            iVar12 = (uint)(*(byte *)(iVar3 + 0x136) >> 3) + iVar3;
            bVar7 = *(byte *)(iVar12 + 0x130);
            uVar11 = *(byte *)(iVar3 + 0x136) & 7;
            if (((int)(uint)bVar7 >> uVar11 & 1U) == 0) {
              *(byte *)(iVar12 + 0x130) = (byte)(1 << uVar11) | bVar7;
            }
            else {
              uStack_38 = 0xffffffff;
              uStack_34 = 0x1f;
              FUN_ram_200012e0((int)((*(byte *)(iVar3 + 0x32) - 10) * 0x1000000) >> 0x18,&uStack_38)
              ;
              if (((*(uint *)(iVar3 + 0x138) != (uStack_38 & *(uint *)(iVar3 + 0x138))) ||
                  (*(uint *)(iVar3 + 0x13c) != (uStack_34 & *(uint *)(iVar3 + 0x13c)))) &&
                 (uVar11 = FUN_ram_000582da(&uStack_38), 2 < uVar11)) {
                tmos_memset(iVar3 + 0x17d,0,10);
                uVar6 = uStack_34;
                uVar11 = uStack_38;
                iVar12 = 0;
                do {
                  uVar9 = FUN_ram_0006ba8a(uVar11,uVar6,iVar12);
                  iVar15 = ((int)(char)iVar12 >> 2) + iVar3;
                  iVar13 = ((int)(char)iVar12 & 3U) << 1;
                  if ((uVar9 & 1) == 0) {
                    bVar7 = (byte)(3 << iVar13);
                  }
                  else {
                    bVar7 = (byte)(1 << iVar13);
                  }
                  *(byte *)(iVar15 + 0x17d) = *(byte *)(iVar15 + 0x17d) | bVar7;
                  iVar12 = iVar12 + 1;
                } while (iVar12 != 0x25);
                *(byte *)(iVar3 + 0x174) = *(byte *)(iVar3 + 0x174) | 8;
              }
            }
          }
          if ((*(ushort *)(iVar3 + 0x3e) != 0) && ((uint)*(ushort *)(iVar3 + 0x3e) % 100 == 0)) {
            if (((DAT_ram_20001e7c & 2) != 0) && (DAT_ram_20001bec != (code *)0x0)) {
              (*DAT_ram_20001bec)(9,CONCAT22(DAT_ram_20001d70,_DAT_ram_20001d72));
              (*DAT_ram_20001bec)(10,DAT_ram_20001d6e);
              (*DAT_ram_20001bec)(0xb,(int)*(short *)(iVar3 + 0x30));
              (*DAT_ram_20001bec)(0xc,(int)*(char *)(iVar3 + 0x32));
            }
            DAT_ram_20001d6e = 0;
            _DAT_ram_20001d70 = 0;
          }
          goto LAB_ram_000615fc;
        }
        goto LAB_ram_0006177e;
      }
      goto LAB_ram_00060df4;
    }
    if (cVar1 != -0x2e) {
LAB_ram_0006129c:
      FUN_ram_00062262();
      goto LAB_ram_000615fc;
    }
    if ((DAT_ram_20001e95 & 1) != 0) {
      DAT_ram_20001e95 = 0;
      if ((-1 < *(int *)(iVar3 + 0xa0) << 0x12) && (iVar12 = FUN_ram_2000082c(iVar3), iVar12 == 1))
      {
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
          FUN_ram_00061bec(1,iVar3);
          puVar4 = DAT_ram_20001e88;
          *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f;
          *puVar4 = *puVar4 & 0xfffffe7f | 0x100;
          *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
          uVar11 = 0xf9;
        }
        DAT_ram_20001eb0[0x14] = uVar11;
        puVar4 = DAT_ram_20001eb0;
        *(undefined1 *)(iVar3 + 0xe) = 0xd1;
        puVar4[3] = 0xd00f;
        puVar5 = DAT_ram_20001eb0;
        puVar4 = DAT_ram_20001e88;
        fence.i();
        DAT_ram_20001eb0[2] = 0x2000;
        DAT_ram_20001e98 = 0x80;
        if ((*puVar4 >> 0xc & 3) == 2) {
          uVar11 = 0x43e;
        }
        else if ((*puVar4 >> 0xc & 3) == 0) {
          uVar11 = 0x196;
        }
        else {
          uVar11 = 0x1be;
        }
        puVar5[0x19] = uVar11;
        puVar5[3] = 0xf00f;
        goto LAB_ram_00060f76;
      }
      FUN_ram_00062262();
      if (*(byte *)(iVar3 + 0x19) != 0) {
        if ((*(byte *)(iVar3 + 0x19) & 0xf0) != 0) {
          uVar8 = FUN_ram_00056968(iVar3,0x3d);
          *(undefined1 *)(iVar3 + 0x2a) = uVar8;
        }
        if (DAT_ram_20001bec != (code *)0x0) {
          (*DAT_ram_20001bec)(0x85,5);
        }
      }
      goto LAB_ram_0006177e;
    }
    if (DAT_ram_20001eb0[0x19] == 0) {
      DAT_ram_20001e98 = 0;
      FUN_ram_00062262();
LAB_ram_0006177e:
      FUN_ram_00056dec(iVar3);
LAB_ram_000615fc:
      FUN_ram_00056878(iVar3);
      return;
    }
  } while( true );
}

