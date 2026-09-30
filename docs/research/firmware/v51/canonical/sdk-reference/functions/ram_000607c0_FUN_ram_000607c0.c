/* Address: ram:000607c0; name: FUN_ram_000607c0; body bytes: 1514 */

void FUN_ram_000607c0(int param_1)

{
  byte bVar1;
  uint *puVar2;
  int iVar3;
  undefined4 uVar4;
  byte bVar5;
  undefined1 uVar6;
  uint uVar7;
  
  gp = 0x20004000;
  *(char *)(param_1 + 0x34) = *(char *)(param_1 + 0x34) + '\x01';
  if (*(char *)(param_1 + 0x13) != '\0') {
    DAT_ram_20001d70 = DAT_ram_20001d70 + 1;
    goto LAB_ram_0006083c;
  }
  *(undefined1 *)(param_1 + 0x13) = 0x40;
  bVar5 = *(byte *)(param_1 + 0x11);
  *(byte *)(param_1 + 0xc) = *(byte *)(param_1 + 0xc) & 0xef | 3;
  *(undefined1 *)(param_1 + 0x1b) = 0;
  if ((char)bVar5 < '\0') {
    *(byte *)(param_1 + 0x11) = bVar5 & 0x7f;
    goto LAB_ram_0006081a;
  }
  uVar7 = *(uint *)(param_1 + 0xa8);
  if ((uVar7 & 2) == 0) {
    if ((uVar7 & 1) == 0) {
      bVar1 = *(byte *)(param_1 + 0x10);
      if (bVar1 == 1) {
        if (uVar7 == 0) {
          uVar7 = *(uint *)(param_1 + 0xa4);
          if (uVar7 == 0) goto LAB_ram_00060b5a;
          if ((uVar7 & 0x40) == 0) {
            if ((uVar7 & 0x100) == 0) {
              if ((uVar7 & 0x200) == 0) {
                if ((uVar7 & 0x400) == 0) {
                  if ((int)(uVar7 << 0x14) < 0) {
                    *(uint *)(param_1 + 0xa4) = uVar7 & 0xfffff7ff;
                    FUN_ram_0005c4a0();
                  }
                  else if ((int)(uVar7 << 0x13) < 0) {
                    if ((bVar5 & 0x13) != 0) goto LAB_ram_0006081a;
                    *(uint *)(param_1 + 0xa4) = uVar7 & 0xffffefff;
                    FUN_ram_0005adbc();
                  }
                  else if ((int)(uVar7 << 0x11) < 0) {
                    *(uint *)(param_1 + 0xa4) = uVar7 & 0xffffbfff;
                    FUN_ram_0005af82();
                  }
                  else if ((int)(uVar7 << 0xe) < 0) {
                    *(uint *)(param_1 + 0xa4) = uVar7 & 0xfffdffff;
                    FUN_ram_0005afca();
                  }
                  else if ((int)(uVar7 << 0xb) < 0) {
                    *(uint *)(param_1 + 0xa4) = uVar7 & 0xffefffff;
                    FUN_ram_0005b0a2();
                  }
                  else {
                    if (-1 < (int)(uVar7 << 8)) {
                      *(undefined4 *)(param_1 + 0xa4) = 0;
                      goto LAB_ram_000608a4;
                    }
                    *(uint *)(param_1 + 0xa4) = uVar7 & 0xff7fffff;
                    FUN_ram_0005b4bc();
                  }
                }
                else {
                  *(uint *)(param_1 + 0xa4) = uVar7 & 0xfffffbff;
                  FUN_ram_0005ad74();
                }
              }
              else {
                if ((bVar5 & 0x13) != 0) goto LAB_ram_0006081a;
                *(uint *)(param_1 + 0xa4) = uVar7 & 0xfffffdff;
                FUN_ram_0005b374();
              }
            }
            else {
              *(uint *)(param_1 + 0xa4) = uVar7 & 0xfffffeff;
              FUN_ram_0005b324();
            }
          }
          else {
            *(uint *)(param_1 + 0xa4) = uVar7 & 0xffffffbf;
            FUN_ram_0005aca6();
          }
        }
        else if ((uVar7 & 0x10) == 0) {
          if ((uVar7 & 0x20) == 0) {
            if ((uVar7 & 0x40) == 0) {
              if ((uVar7 & 0x80) == 0) {
                if ((uVar7 & 0x100) == 0) {
                  if ((uVar7 & 0x200) == 0) {
                    if ((uVar7 & 0x400) != 0) {
                      *(uint *)(param_1 + 0xa8) = uVar7 & 0xfffffbff;
                      goto LAB_ram_0006095a;
                    }
                    if ((int)(uVar7 << 0x14) < 0) {
                      *(uint *)(param_1 + 0xa8) = uVar7 & 0xfffff7ff;
                      FUN_ram_0005b020();
                    }
                    else {
                      if (-1 < (int)(uVar7 << 0x13)) {
                        *(undefined4 *)(param_1 + 0xa8) = 0;
                        goto LAB_ram_000608a4;
                      }
                      *(uint *)(param_1 + 0xa8) = uVar7 & 0xffffefff;
                      FUN_ram_0005b124();
                    }
                  }
                  else {
                    *(uint *)(param_1 + 0xa8) = uVar7 & 0xfffffdff;
                    FUN_ram_0005b70c();
                  }
                }
                else {
                  *(uint *)(param_1 + 0xa8) = uVar7 & 0xfffffeff;
LAB_ram_00060930:
                  FUN_ram_0005ae46(param_1);
                }
              }
              else {
                *(uint *)(param_1 + 0xa8) = uVar7 & 0xffffff7f;
LAB_ram_0006091a:
                FUN_ram_0005c572(param_1);
              }
            }
            else {
              *(uint *)(param_1 + 0xa8) = uVar7 & 0xffffffbf;
              FUN_ram_0005ada2();
            }
          }
          else {
            *(uint *)(param_1 + 0xa8) = uVar7 & 0xffffffdf;
            FUN_ram_0005b41e();
          }
        }
        else {
          *(uint *)(param_1 + 0xa8) = uVar7 & 0xffffffef;
LAB_ram_000608de:
          FUN_ram_0005b2d4();
        }
      }
      else {
        if (bVar1 != 0) {
          if (bVar1 < 0x47) {
            if (bVar1 < 0x45) {
              if (bVar1 == 0x2a) {
                FUN_ram_0005abec();
                if (*(char *)(param_1 + 0x4b) != '\0') {
                  tmos_memcpy(param_1 + 0xcc,param_1 + 0xac,0x10);
                }
                *(undefined4 *)(param_1 + 0xec) = 0;
                *(undefined4 *)(param_1 + 0xf0) = 0;
                *(byte *)(param_1 + 0x4a) = *(byte *)(param_1 + 0x4a) | 1;
              }
              else if (bVar1 < 0x2b) {
                if (bVar1 == 0x21) {
                  if ((*(uint *)(param_1 + 0x108) & 1) == 0) {
                    *(undefined1 *)(param_1 + 0x2a) = 0x1a;
                    if ((*(uint *)(param_1 + 0x100) & 4) == 0) {
LAB_ram_00060c76:
                      FUN_ram_0005ad24(param_1);
                    }
                    else {
                      uVar6 = 3;
LAB_ram_00060bd6:
                      *(undefined1 *)(param_1 + 0x2b) = uVar6;
                      FUN_ram_0005ad4a(param_1);
                    }
LAB_ram_00060bc4:
                    *(undefined1 *)(param_1 + 0x10) = 1;
                  }
                  else {
                    FUN_ram_0005b22c();
                  }
                }
                else {
                  if (bVar1 < 0x22) {
                    if (bVar1 == 0x1b) {
                      FUN_ram_0005abba();
                      *(undefined1 *)(param_1 + 0x52) = 0x16;
                      goto LAB_ram_0006083c;
                    }
                    bVar5 = 0x1d;
                  }
                  else {
                    if (bVar1 == 0x25) {
                      if ((*(uint *)(param_1 + 0x100) & 4) == 0) {
                        FUN_ram_0005ad24();
                      }
                      else {
                        *(undefined1 *)(param_1 + 0x2b) = 3;
                        FUN_ram_0005ad4a();
                      }
                      *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) & 0xf7;
                      goto LAB_ram_00060bc4;
                    }
                    bVar5 = 0x27;
                  }
                  if (bVar1 != bVar5) goto LAB_ram_0006081a;
                  FUN_ram_0005cde4(param_1);
                  *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) | 1;
LAB_ram_00060c2c:
                  *(undefined1 *)(param_1 + 0x10) = 0;
                }
              }
              else {
                if (bVar1 != 0x36) {
                  if (bVar1 < 0x37) {
                    if (bVar1 == 0x2e) {
                      *(undefined4 *)(param_1 + 0xe4) = 0;
                      *(undefined4 *)(param_1 + 0xe8) = 0;
                      *(byte *)(param_1 + 0x4a) = *(byte *)(param_1 + 0x4a) | 2;
                      FUN_ram_0005ac0e();
                      *(undefined1 *)(param_1 + 0x2a) = 0;
                      *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) & 0xf7;
                      uVar7 = *(uint *)(param_1 + 0xa0) | 0x10;
LAB_ram_00060bee:
                      *(uint *)(param_1 + 0xa0) = uVar7;
                      goto LAB_ram_00060bc4;
                    }
                    if (bVar1 == 0x31) goto LAB_ram_000608de;
                  }
                  else {
                    if (bVar1 != 0x40) {
                      if (bVar1 == 0x41) {
                        if (*(char *)(param_1 + 0x2a) != '\0') {
                          if (*(char *)(param_1 + 0x2a) != '\x01') {
                            if ((*(uint *)(param_1 + 0x100) & 4) == 0) goto LAB_ram_00060c76;
                            uVar6 = 0xf;
                            goto LAB_ram_00060bd6;
                          }
                          FUN_ram_0005b41e();
                          goto LAB_ram_00060bc4;
                        }
                        FUN_ram_0005cde4();
                        uVar7 = *(uint *)(param_1 + 0xa0) | 2;
                        goto LAB_ram_00060bee;
                      }
                      if (bVar1 != 0x38) goto LAB_ram_0006081a;
                      FUN_ram_0005cde4();
                      goto LAB_ram_00060c2c;
                    }
                    if ((uVar7 & 0x400) != 0) {
                      *(uint *)(param_1 + 0xa8) = uVar7 & 0xfffffbff;
                      FUN_ram_0005aff2();
                      *(undefined1 *)(param_1 + 0x10) = 0x40;
                      goto LAB_ram_0006083c;
                    }
                  }
                  goto LAB_ram_0006081a;
                }
                iVar3 = FUN_ram_20000628();
                if (iVar3 != 0) {
                  *(undefined1 *)(param_1 + 0x4b) = 1;
                  FUN_ram_0005ac84(param_1);
                  *(byte *)(param_1 + 0x4a) = *(byte *)(param_1 + 0x4a) & 0xfe;
                }
              }
            }
            else {
              FUN_ram_0005cde4();
              *(undefined1 *)(param_1 + 0x10) = 1;
              *(undefined2 *)(param_1 + 0x60) = 0;
              *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) | 4;
            }
            goto LAB_ram_0006083c;
          }
          if (bVar1 == 0x5a) {
            if ((*(byte *)(param_1 + 0x14a) != 0) &&
               (1 << (*(byte *)(param_1 + 0x146) & 0x1f) != (uint)*(byte *)(param_1 + 0x14a))) {
              *(byte *)(param_1 + 0x11) = bVar5 | 0x10;
            }
            if ((*(byte *)(param_1 + 0x14b) != 0) &&
               (1 << (*(byte *)(param_1 + 0x147) & 0x1f) != (uint)*(byte *)(param_1 + 0x14b))) {
              *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x10;
            }
            if ((*(char *)(param_1 + 0x1e) == '\0') || ((*(byte *)(param_1 + 0x11) & 0x10) != 0)) {
              if ((*(char *)(param_1 + 0x161) != '\0') && ((*(uint *)(param_1 + 0x104) & 2) != 0)) {
                *(uint *)(param_1 + 0xa4) = *(uint *)(param_1 + 0xa4) | 0x100000;
              }
            }
            else {
              *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) | 0x200;
            }
            FUN_ram_0005cde4(param_1);
            goto LAB_ram_00060bc4;
          }
          if (bVar1 < 0x5b) {
            if (bVar1 == 0x55) {
LAB_ram_00060b5a:
              iVar3 = FUN_ram_20000628(param_1);
              if (iVar3 == 0) goto LAB_ram_0006083c;
            }
            else if (bVar1 < 0x56) {
              if (bVar1 == 0x4b) {
                FUN_ram_0005ada2();
                goto LAB_ram_00060bc4;
              }
              if (bVar1 == 0x51) goto LAB_ram_0006091a;
            }
            else {
              if (bVar1 == 0x56) goto LAB_ram_00060930;
              if (bVar1 == 0x58) goto LAB_ram_00060b5a;
            }
          }
          else if (bVar1 < 0x6c) {
            if (0x69 < bVar1) {
              FUN_ram_0005cde4();
              uVar7 = *(uint *)(param_1 + 0xa0) | 0x800;
              goto LAB_ram_00060bee;
            }
            if (bVar1 == 0x66) {
              FUN_ram_0005b70c();
              goto LAB_ram_00060bc4;
            }
          }
          else {
            if (bVar1 == 0x76) {
LAB_ram_0006095a:
              FUN_ram_0005aff2(param_1);
              goto LAB_ram_0006083c;
            }
            if (bVar1 == 0x86) {
              FUN_ram_0005b124();
              goto LAB_ram_00060bc4;
            }
          }
        }
LAB_ram_0006081a:
        FUN_ram_0005cde4(param_1);
      }
      goto LAB_ram_0006083c;
    }
    *(uint *)(param_1 + 0xa8) = uVar7 & 0xfffffffe;
  }
  else {
    *(uint *)(param_1 + 0xa8) = uVar7 & 0xfffffffd;
    if ((*(uint *)(param_1 + 0x100) & 4) == 0) {
      FUN_ram_0005ad24();
    }
    else {
      FUN_ram_0005ad4a();
    }
LAB_ram_0006083c:
    if (*(char *)(param_1 + 0x1b) == '\x01') {
      **(undefined1 **)(*(int *)(param_1 + 0x118) + 4) = *(undefined1 *)(param_1 + 0xc);
      *(undefined1 *)(*(int *)(*(int *)(param_1 + 0x118) + 4) + 1) = *(undefined1 *)(param_1 + 0x15)
      ;
      uVar4 = *(undefined4 *)(*(int *)(param_1 + 0x118) + 4);
      goto LAB_ram_0006086c;
    }
  }
LAB_ram_000608a4:
  **(undefined1 **)(param_1 + 0x110) = *(undefined1 *)(param_1 + 0xc);
  *(undefined1 *)(*(int *)(param_1 + 0x110) + 1) = *(undefined1 *)(param_1 + 0x15);
  uVar4 = *(undefined4 *)(param_1 + 0x110);
LAB_ram_0006086c:
  *(undefined4 *)(DAT_ram_20001eb0 + 0x70) = uVar4;
  puVar2 = DAT_ram_20001e88;
  *DAT_ram_20001e88 = *DAT_ram_20001e88 | 0x800000;
  puVar2[0xb] = puVar2[0xb] & 0xfffffffc;
  return;
}

