/* Address: ram:00059986; name: FUN_ram_00059986; body bytes: 1372 */

void FUN_ram_00059986(int param_1)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  byte bVar4;
  uint uVar5;
  
  gp = 0x20004000;
  *(char *)(param_1 + 0x34) = *(char *)(param_1 + 0x34) + '\x01';
  if (*(char *)(param_1 + 0x13) != '\0') {
    DAT_ram_20001d70 = DAT_ram_20001d70 + 1;
    goto LAB_ram_000599fa;
  }
  *(undefined1 *)(param_1 + 0x13) = 0x40;
  bVar4 = *(byte *)(param_1 + 0x11);
  *(byte *)(param_1 + 0xc) = *(byte *)(param_1 + 0xc) & 0xec | 3;
  *(undefined1 *)(param_1 + 0x1b) = 0;
  if ((char)bVar4 < '\0') {
    *(byte *)(param_1 + 0x11) = bVar4 & 0x7f;
    goto LAB_ram_000599d8;
  }
  uVar5 = *(uint *)(param_1 + 0xa8);
  if ((uVar5 & 2) == 0) {
    if ((uVar5 & 1) != 0) {
      *(uint *)(param_1 + 0xa8) = uVar5 & 0xfffffffe;
      FUN_ram_0005ac30();
      goto LAB_ram_000599fa;
    }
    bVar1 = *(byte *)(param_1 + 0x10);
    if (bVar1 != 1) {
      if (bVar1 == 0) goto LAB_ram_000599d8;
      if (bVar1 < 0x47) {
        if (bVar1 < 0x45) {
          if (bVar1 == 0x2c) {
            *(undefined1 *)(param_1 + 0x4a) = 3;
            *(undefined4 *)(param_1 + 0xe4) = 0;
            *(undefined4 *)(param_1 + 0xe8) = 0;
            *(undefined4 *)(param_1 + 0xec) = 0;
            *(undefined4 *)(param_1 + 0xf0) = 0;
            FUN_ram_0005ac0e();
          }
          else if (bVar1 < 0x2d) {
            if (bVar1 != 0x23) {
              if (bVar1 < 0x24) {
                if (bVar1 == 0x1a) {
                  FUN_ram_0005abba();
                  *(undefined1 *)(param_1 + 0x52) = 0x16;
                  goto LAB_ram_000599fa;
                }
                bVar4 = 0x1d;
              }
              else {
                if (bVar1 == 0x26) goto LAB_ram_00059e92;
                bVar4 = 0x27;
              }
              if (bVar1 == bVar4) {
                FUN_ram_0005cde4(param_1);
                *(undefined1 *)(param_1 + 0x10) = 0;
                *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) | 1;
                goto LAB_ram_000599fa;
              }
            }
LAB_ram_000599d8:
            FUN_ram_0005cde4(param_1);
          }
          else if (bVar1 == 0x37) {
            *(undefined1 *)(param_1 + 0x4b) = 1;
            tmos_memcpy(param_1 + 0xcc,param_1 + 0xac,0x10);
LAB_ram_00059bf4:
            FUN_ram_0005b5e4(param_1);
          }
          else {
            if (bVar1 < 0x38) {
              if (bVar1 == 0x2e) {
LAB_ram_00059e92:
                FUN_ram_0005cde4(param_1);
                *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) & 0xf7;
                uVar5 = *(uint *)(param_1 + 0xa0) | 0x10;
                goto LAB_ram_00059eaa;
              }
              if (bVar1 == 0x31) goto LAB_ram_00059a68;
              goto LAB_ram_000599d8;
            }
            if (bVar1 == 0x38) {
              FUN_ram_0005ac84();
            }
            else {
              if (bVar1 != 0x41) goto LAB_ram_000599d8;
              if (*(char *)(param_1 + 0x2a) == '\x1e') {
                if ((*(uint *)(param_1 + 0x100) & 4) == 0) {
                  FUN_ram_0005ad24();
                }
                else {
                  *(undefined1 *)(param_1 + 0x2b) = 0xf;
                  FUN_ram_0005ad4a();
                }
                goto LAB_ram_00059d2e;
              }
              if (*(char *)(param_1 + 0x2a) == '\x01') {
                *(short *)(param_1 + 0x56) =
                     (short)((int)((uint)*(ushort *)(param_1 + 0x72) +
                                  (uint)*(ushort *)(param_1 + 0x74)) >> 1);
                goto LAB_ram_00059b74;
              }
              FUN_ram_0005cde4();
              *(undefined1 *)(param_1 + 0x10) = 1;
              *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) | 2;
            }
          }
        }
        else {
          *(short *)(param_1 + 0x56) =
               (short)((int)((uint)*(ushort *)(param_1 + 0x72) + (uint)*(ushort *)(param_1 + 0x74))
                      >> 1);
LAB_ram_00059e1a:
          FUN_ram_0005aae2();
LAB_ram_00059d6e:
          *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 1;
        }
      }
      else {
        if (bVar1 < 0x58) {
          if (0x55 < bVar1) {
LAB_ram_00059c44:
            FUN_ram_0005aed8();
            goto LAB_ram_000599fa;
          }
          if (bVar1 != 0x4b) {
            if (bVar1 < 0x4c) {
              if (bVar1 == 0x47) {
                if (*(char *)(param_1 + 0x2a) != '\x1e') {
                  *(short *)(param_1 + 0x56) =
                       (short)((int)((uint)*(ushort *)(param_1 + 0x72) +
                                    (uint)*(ushort *)(param_1 + 0x74)) >> 1);
                  goto LAB_ram_00059e1a;
                }
                FUN_ram_0005ad24();
                *(undefined1 *)(param_1 + 0x10) = 1;
                goto LAB_ram_00059d6e;
              }
            }
            else {
              if (bVar1 == 0x51) goto LAB_ram_00059a90;
              if (bVar1 == 0x55) goto LAB_ram_00059d8c;
            }
            goto LAB_ram_000599d8;
          }
          FUN_ram_0005ada2();
        }
        else if (bVar1 < 0x6c) {
          if (bVar1 < 0x6a) {
            if (bVar1 == 0x61) {
              FUN_ram_0005cde4();
            }
            else {
              if (bVar1 != 0x66) goto LAB_ram_000599d8;
              FUN_ram_0005b70c();
            }
          }
          else {
            FUN_ram_0005cde4();
            uVar5 = *(uint *)(param_1 + 0xa0) | 0x800;
LAB_ram_00059eaa:
            *(uint *)(param_1 + 0xa0) = uVar5;
          }
        }
        else {
          if (bVar1 == 0x76) {
LAB_ram_00059ab8:
            FUN_ram_0005aff2(param_1);
            goto LAB_ram_000599fa;
          }
          if (bVar1 != 0x86) goto LAB_ram_000599d8;
          FUN_ram_0005b124();
        }
LAB_ram_00059d2e:
        *(undefined1 *)(param_1 + 0x10) = 1;
      }
      goto LAB_ram_000599fa;
    }
    if (uVar5 != 0) {
      if ((uVar5 & 0x10) == 0) {
        if ((uVar5 & 0x40) == 0) {
          if ((uVar5 & 0x80) == 0) {
            if ((uVar5 & 0x200) == 0) {
              if ((uVar5 & 0x400) != 0) {
                *(uint *)(param_1 + 0xa8) = uVar5 & 0xfffffbff;
                goto LAB_ram_00059ab8;
              }
              if (-1 < (int)(uVar5 << 0x13)) {
                *(undefined4 *)(param_1 + 0xa8) = 0;
                goto LAB_ram_00059adc;
              }
              *(uint *)(param_1 + 0xa8) = uVar5 & 0xffffefff;
              FUN_ram_0005b124();
            }
            else {
              *(uint *)(param_1 + 0xa8) = uVar5 & 0xfffffdff;
              FUN_ram_0005b70c();
            }
          }
          else {
            *(uint *)(param_1 + 0xa8) = uVar5 & 0xffffff7f;
LAB_ram_00059a90:
            FUN_ram_0005c572();
          }
        }
        else {
          *(uint *)(param_1 + 0xa8) = uVar5 & 0xffffffbf;
          FUN_ram_0005ada2();
        }
      }
      else {
        *(uint *)(param_1 + 0xa8) = uVar5 & 0xffffffef;
LAB_ram_00059a68:
        FUN_ram_0005b2d4();
      }
      goto LAB_ram_000599fa;
    }
    uVar5 = *(uint *)(param_1 + 0xa4);
    if (uVar5 == 0) {
LAB_ram_00059d8c:
      iVar2 = FUN_ram_20000628();
      if (iVar2 != 0) goto LAB_ram_000599d8;
      goto LAB_ram_000599fa;
    }
    if ((uVar5 & 0x10) != 0) {
      *(uint *)(param_1 + 0xa4) = uVar5 & 0xffffffef;
      FUN_ram_0005b284();
      goto LAB_ram_000599fa;
    }
    if ((uVar5 & 0x40) != 0) {
      *(uint *)(param_1 + 0xa4) = uVar5 & 0xffffffbf;
      FUN_ram_0005aca6();
      goto LAB_ram_000599fa;
    }
    if ((uVar5 & 0x200) != 0) {
      if ((bVar4 & 0x13) != 0) goto LAB_ram_000599d8;
      if ((*(int *)(param_1 + 0x188) == 0) || (iVar2 = FUN_ram_20000628(), iVar2 != 0)) {
        *(undefined4 *)(param_1 + 0x188) = 0;
        *(uint *)(param_1 + 0xa4) = *(uint *)(param_1 + 0xa4) & 0xfffffdff;
        FUN_ram_0005b374(param_1);
      }
      goto LAB_ram_000599fa;
    }
    if ((uVar5 & 1) != 0) {
      if ((bVar4 & 0x13) != 0) goto LAB_ram_000599d8;
      *(uint *)(param_1 + 0xa4) = uVar5 & 0xfffffffe;
LAB_ram_00059b74:
      FUN_ram_0005aae2(param_1);
      goto LAB_ram_000599fa;
    }
    if ((uVar5 & 2) != 0) {
      if ((bVar4 & 0x13) != 0) goto LAB_ram_000599d8;
      *(uint *)(param_1 + 0xa4) = uVar5 & 0xfffffffd;
      FUN_ram_0005b1c6();
      goto LAB_ram_000599fa;
    }
    if ((uVar5 & 0x400) != 0) {
      *(uint *)(param_1 + 0xa4) = uVar5 & 0xfffffbff;
      FUN_ram_0005ad74();
      goto LAB_ram_000599fa;
    }
    if ((int)(uVar5 << 0x14) < 0) {
      *(uint *)(param_1 + 0xa4) = uVar5 & 0xfffff7ff;
      FUN_ram_0005c4a0();
      goto LAB_ram_000599fa;
    }
    if ((uVar5 & 0x20) != 0) {
      iVar2 = FUN_ram_20000628();
      if (iVar2 != 0) {
        *(uint *)(param_1 + 0xa4) = *(uint *)(param_1 + 0xa4) & 0xffffffdf;
        FUN_ram_0005ac56(param_1);
      }
      goto LAB_ram_000599fa;
    }
    if ((uVar5 & 8) != 0) {
      *(uint *)(param_1 + 0xa4) = uVar5 & 0xfffffff7;
      goto LAB_ram_00059bf4;
    }
    if (-1 < (int)uVar5) {
      if ((int)(uVar5 << 0x13) < 0) {
        if ((bVar4 & 0x13) != 0) goto LAB_ram_000599d8;
        *(uint *)(param_1 + 0xa4) = uVar5 & 0xffffefff;
        FUN_ram_0005adbc();
      }
      else {
        if ((int)(uVar5 << 0x12) < 0) {
          *(uint *)(param_1 + 0xa4) = uVar5 & 0xffffdfff;
          goto LAB_ram_00059c44;
        }
        if ((int)(uVar5 << 0xe) < 0) {
          *(uint *)(param_1 + 0xa4) = uVar5 & 0xfffdffff;
          FUN_ram_0005afca();
        }
        else if ((int)(uVar5 << 0xb) < 0) {
          *(uint *)(param_1 + 0xa4) = uVar5 & 0xffefffff;
          FUN_ram_0005b0a2();
        }
        else {
          if (-1 < (int)(uVar5 << 9)) {
            *(undefined4 *)(param_1 + 0xa4) = 0;
            goto LAB_ram_00059adc;
          }
          *(uint *)(param_1 + 0xa4) = uVar5 & 0xffbfffff;
          FUN_ram_0005b18e();
        }
      }
      goto LAB_ram_000599fa;
    }
    *(uint *)(param_1 + 0xa4) = uVar5 & 0x7fffffff;
    *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) | 2;
  }
  else {
    *(uint *)(param_1 + 0xa8) = uVar5 & 0xfffffffd;
    if ((*(uint *)(param_1 + 0x100) & 4) == 0) {
      FUN_ram_0005ad24();
    }
    else {
      FUN_ram_0005ad4a();
    }
LAB_ram_000599fa:
    if (*(char *)(param_1 + 0x1b) == '\x01') {
      **(undefined1 **)(*(int *)(param_1 + 0x118) + 4) = *(undefined1 *)(param_1 + 0xc);
      *(undefined1 *)(*(int *)(*(int *)(param_1 + 0x118) + 4) + 1) = *(undefined1 *)(param_1 + 0x15)
      ;
      uVar3 = *(undefined4 *)(*(int *)(param_1 + 0x118) + 4);
      goto LAB_ram_00059a2a;
    }
  }
LAB_ram_00059adc:
  **(undefined1 **)(param_1 + 0x110) = *(undefined1 *)(param_1 + 0xc);
  *(undefined1 *)(*(int *)(param_1 + 0x110) + 1) = *(undefined1 *)(param_1 + 0x15);
  uVar3 = *(undefined4 *)(param_1 + 0x110);
LAB_ram_00059a2a:
  *(undefined4 *)(DAT_ram_20001eb0 + 0x70) = uVar3;
  return;
}

