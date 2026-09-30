/* Address: 00010f24; name: FUN_00010f24; body bytes: 810 */

/* WARNING: Type propagation algorithm not settling */

int FUN_00010f24(undefined4 param_1,undefined4 *param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  bool bVar10;
  undefined4 local_58;
  undefined4 *local_54;
  uint local_50 [9];
  undefined4 local_2c;
  undefined4 *puStack_28;
  
  iVar9 = 0;
  local_54 = param_2 + 3;
  bVar1 = true;
  iVar8 = 0;
  local_2c = param_1;
  puStack_28 = param_2;
LAB_00010f40:
  do {
    while( true ) {
      iVar2 = (*(code *)param_2[5])(local_54,1);
      if (iVar2 == 0) {
        return iVar9;
      }
      if (iVar2 == 0x25) break;
      iVar3 = (*(code *)param_2[8])();
      if (iVar3 == 0) {
        iVar3 = (*(code *)param_2[6])(local_2c);
        if (iVar3 != iVar2) {
          (*(code *)param_2[7])(local_2c);
          goto joined_r0x00010fa0;
        }
LAB_00010f94:
        iVar8 = iVar8 + 1;
      }
      else {
        do {
          (*(code *)param_2[5])(local_54,1);
          iVar2 = (*(code *)param_2[8])();
        } while (iVar2 != 0);
        (*(code *)param_2[5])(local_54,0xffffffff);
        while( true ) {
          (*(code *)param_2[6])(local_2c);
          iVar2 = (*(code *)param_2[8])();
          if (iVar2 == 0) break;
          iVar8 = iVar8 + 1;
        }
        (*(code *)param_2[7])(local_2c);
      }
    }
    iVar3 = 0;
    iVar2 = (*(code *)param_2[5])(local_54,0);
    if (iVar2 == 0x2a) {
      (*(code *)param_2[5])(local_54,1);
    }
    uVar7 = (uint)(iVar2 == 0x2a);
    while (iVar2 = (*(code *)param_2[5])(local_54,1), iVar2 - 0x30U < 10) {
      if (0xccccccc < iVar3) {
        return iVar9;
      }
      iVar3 = iVar2 + iVar3 * 10 + -0x30;
      if (iVar3 < 0) {
        return iVar9;
      }
      uVar7 = uVar7 | 0x10;
    }
    if (-1 < (int)(uVar7 << 0x1b)) {
      iVar3 = 0x7fffffff;
    }
    if (iVar2 == 0x6c) {
      iVar2 = (*(code *)param_2[5])(local_54,1);
      if (iVar2 != 0x6c) {
        uVar7 = uVar7 | 4;
        goto LAB_0001104c;
      }
LAB_00011022:
      uVar7 = uVar7 | 2;
LAB_00011044:
      iVar2 = (*(code *)param_2[5])(local_54,1);
    }
    else {
      if (iVar2 == 0x4c) {
        uVar7 = uVar7 | 0x20;
        goto LAB_00011044;
      }
      if (iVar2 == 0x68) {
        iVar2 = (*(code *)param_2[5])(local_54,1);
        if (iVar2 == 0x68) {
          uVar7 = uVar7 | 0x800;
          goto LAB_00011044;
        }
        uVar7 = uVar7 | 8;
      }
      else {
        if (iVar2 == 0x6a) goto LAB_00011022;
        if ((iVar2 == 0x74) || (iVar2 == 0x7a)) goto LAB_00011044;
      }
    }
LAB_0001104c:
    param_2[1] = uVar7;
    param_2[2] = iVar3;
    if (iVar2 == 0x65) goto LAB_000110d0;
    if (iVar2 < 0x66) {
      if (iVar2 == 0x58) {
LAB_00011150:
        param_2[1] = uVar7 | 0x40;
        if ((int)(uVar7 << 0x1e) < 0) goto LAB_0001115e;
LAB_0001116c:
        uVar6 = 0x10;
LAB_00011170:
        iVar2 = FUN_00010588(0xfffffffe,local_2c,uVar6,param_2);
      }
      else if (iVar2 < 0x59) {
        if (iVar2 != 0x45) {
          if (iVar2 < 0x46) {
            if (iVar2 == 0x25) {
              iVar3 = (*(code *)param_2[6])(local_2c);
              if (iVar3 != 0x25) {
                (*(code *)param_2[7])(local_2c);
joined_r0x00010fa0:
                if (iVar3 != -1) {
                  return iVar9;
                }
                if (iVar9 == 0) {
                  return -1;
                }
                return iVar9;
              }
              goto LAB_00010f94;
            }
            if (iVar2 != 0x41) {
              return iVar9;
            }
          }
          else if ((iVar2 != 0x46) && (iVar2 != 0x47)) {
            return iVar9;
          }
        }
LAB_000110d0:
        iVar2 = FUN_0001137c(0xfffffffe,local_2c,&local_58,param_2);
      }
      else {
        if (iVar2 != 0x5b) {
          if (iVar2 == 0x61) goto LAB_000110d0;
          if (iVar2 != 99) {
            if (iVar2 != 100) {
              return iVar9;
            }
LAB_0001113e:
            param_2[1] = uVar7 | 0x40;
            uVar6 = 10;
            goto joined_r0x000110ee;
          }
        }
LAB_0001117c:
        uVar6 = 0;
        if (iVar2 == 99) {
          if (-1 < (int)((uint)*(byte *)(param_2 + 1) << 0x1b)) {
            param_2[2] = 1;
          }
          uVar6 = 1;
        }
        else if (iVar2 == 0x5b) {
          iVar2 = (*(code *)param_2[5])(local_54,1,(code *)param_2[5],0);
          bVar10 = iVar2 == 0x5e;
          if (bVar10) {
            iVar2 = (*(code *)param_2[5])(local_54,1);
          }
          if (param_2[4] == 0) {
            iVar3 = 0;
            do {
              local_50[iVar3] = 0;
              iVar3 = iVar3 + 1;
            } while (iVar3 < 8);
          }
          do {
            if (iVar2 == 0) {
              return iVar9;
            }
            if (param_2[4] == 0) {
              local_50[(int)(iVar2 + ((uint)(iVar2 >> 0x1f) >> 0x1b)) >> 5] =
                   local_50[(int)(iVar2 + ((uint)(iVar2 >> 0x1f) >> 0x1b)) >> 5] |
                   1 << (iVar2 % 0x20 & 0xffU);
            }
            iVar2 = (*(code *)param_2[5])(local_54,1);
          } while (iVar2 != 0x5d);
          if (bVar10) {
            iVar2 = 0;
            do {
              local_50[iVar2] = ~local_50[iVar2];
              iVar2 = iVar2 + 1;
            } while (iVar2 < 8);
          }
        }
        iVar2 = -2;
        local_58 = uVar6;
      }
LAB_00011220:
      if (iVar2 < 0) {
        if (iVar2 != -1) {
          return iVar9;
        }
        if (bVar1) {
          return -1;
        }
        return iVar9;
      }
      if ((uVar7 & 1) == 0) {
        iVar9 = iVar9 + 1;
      }
      iVar8 = iVar8 + iVar2;
      bVar1 = false;
      goto LAB_00010f40;
    }
    if (iVar2 == 0x6f) {
      param_2[1] = uVar7 | 0x40;
      uVar6 = 8;
joined_r0x000110ee:
      if (-1 < (int)(uVar7 << 0x1e)) goto LAB_00011170;
LAB_0001115e:
      iVar2 = -2;
      goto LAB_00011220;
    }
    if (0x6f < iVar2) {
      if (iVar2 != 0x70) {
        if (iVar2 == 0x73) goto LAB_0001117c;
        if (iVar2 == 0x75) goto LAB_0001113e;
        if (iVar2 != 0x78) {
          return iVar9;
        }
        goto LAB_00011150;
      }
      param_2[1] = uVar7 & 0xfffff7f1;
      goto LAB_0001116c;
    }
    if ((iVar2 == 0x66) || (iVar2 == 0x67)) goto LAB_000110d0;
    if (iVar2 == 0x69) {
      param_2[1] = uVar7 | 0x40;
      uVar6 = 0;
      goto joined_r0x000110ee;
    }
    if (iVar2 != 0x6e) {
      return iVar9;
    }
    if ((uVar7 & 1) == 0) {
      puVar4 = (undefined4 *)*param_2;
      *param_2 = puVar4 + 1;
      piVar5 = (int *)*puVar4;
      if ((int)(uVar7 << 0x14) < 0) {
        *(char *)piVar5 = (char)iVar8;
      }
      else if ((int)(uVar7 << 0x1c) < 0) {
        *(short *)piVar5 = (short)iVar8;
      }
      else if ((int)(uVar7 << 0x1e) < 0) {
        *piVar5 = iVar8;
        piVar5[1] = iVar8 >> 0x1f;
      }
      else {
        *piVar5 = iVar8;
      }
    }
  } while( true );
}

