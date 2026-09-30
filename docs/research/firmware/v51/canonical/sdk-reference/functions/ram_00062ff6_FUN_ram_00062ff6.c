/* Address: ram:00062ff6; name: FUN_ram_00062ff6; body bytes: 1296 */

/* WARNING: Removing unreachable block (ram,0x00063056) */
/* WARNING: Removing unreachable block (ram,0x0006304c) */
/* WARNING: Removing unreachable block (ram,0x00063072) */

void FUN_ram_00062ff6(void)

{
  uint *puVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 uVar5;
  char *pcVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  char acStack_21 [9];
  
  iVar3 = DAT_ram_20001efc;
  pcVar6 = DAT_ram_20001eac;
  gp = 0x20004000;
  if ((DAT_ram_20001eb4 & 1) == 0) {
    if ((DAT_ram_20001e95 & 1) == 0) {
      FUN_ram_0006219c();
      *DAT_ram_20001e88 = *DAT_ram_20001e88 | 0x800000;
      FUN_ram_000628b8();
      if (DAT_ram_20001bec == (code *)0x0) {
        gp = 0x20004000;
        return;
      }
      uVar4 = 1;
      goto LAB_ram_000632de;
    }
    acStack_21[0] = '\0';
    DAT_ram_20001e95 = 0;
    FUN_ram_000628b8();
    if ((DAT_ram_20001ee0 & 4) != 0) {
      if (pcVar6[(byte)pcVar6[1]] == -0x80) {
        DAT_ram_20001eb4 = DAT_ram_20001eb4 | 8;
      }
      if ((DAT_ram_20001bd2 < '\0') || (3 < DAT_ram_20001ea4)) {
        DAT_ram_20001ea4 = DAT_ram_20001ea4 - 4;
      }
      else {
        DAT_ram_20001ea4 = DAT_ram_20001ea4 + 0xa8bffffc;
      }
      uVar7 = DAT_ram_20001ea4;
      if ((-1 < DAT_ram_20001bd2) && (DAT_ram_20001ea4 < DAT_ram_20001edc)) {
        uVar7 = DAT_ram_20001ea4 + 0xa8c00000;
      }
      uVar7 = uVar7 - DAT_ram_20001edc;
      uVar8 = (uint)(byte)pcVar6[(byte)pcVar6[1] + 1];
      uVar9 = uVar8 * 8;
      if ((char)DAT_ram_20001ee0 < '\0') {
        if (uVar9 < uVar7) {
          uVar7 = uVar7 + uVar8 * -8;
        }
        else {
          uVar7 = uVar9 - uVar7;
        }
        if (uVar7 < 0x21) {
          uVar7 = DAT_ram_20001ea4;
          if ((-1 < DAT_ram_20001bd2) && (DAT_ram_20001ea4 < uVar9)) {
            uVar7 = DAT_ram_20001ea4 + 0xa8c00000;
          }
          DAT_ram_20001edc = uVar7 + uVar8 * -8;
        }
      }
      else {
        uVar7 = DAT_ram_20001ea4;
        if ((-1 < DAT_ram_20001bd2) && (DAT_ram_20001ea4 < uVar9)) {
          uVar7 = DAT_ram_20001ea4 + 0xa8c00000;
        }
        DAT_ram_20001edc = uVar7 + uVar8 * -8;
        DAT_ram_20001ee0 = DAT_ram_20001ee0 | 0x80;
      }
      tmos_set_event(DAT_ram_20001ee4,2);
      iVar3 = DAT_ram_20001eb0;
      if ((DAT_ram_20001eb4 & 8) != 0) {
        *(undefined4 *)(DAT_ram_20001eb0 + 100) = 200;
        *DAT_ram_20001ea8 = 0xff;
        puVar1 = DAT_ram_20001e88;
        DAT_ram_20001e96 = 0;
        DAT_ram_20001e97 = 0;
        DAT_ram_20001e98 = 0;
        DAT_ram_20001e99 = 0;
        *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f;
        *puVar1 = *puVar1 & 0xfffffe7f | 0x100;
        uVar7 = (uint)DAT_ram_20001eb4;
        *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
        *(undefined4 *)(iVar3 + 0x50) = 0xda;
        FUN_ram_200011be(0,(int)uVar7 >> 4 & 3,1);
        DAT_ram_20001eb4 = DAT_ram_20001eb4 & 0xf7;
        goto LAB_ram_00063422;
      }
      pcVar6[1] = pcVar6[1] + -2;
    }
    cVar2 = FUN_ram_20001120(DAT_ram_20001eac,0,acStack_21,0);
    uVar7 = (uint)cVar2;
    if (((*DAT_ram_20001eac != -1) && (DAT_ram_20001ed4._3_1_ != -1)) &&
       (*DAT_ram_20001eac != DAT_ram_20001ed4._3_1_)) {
      uVar7 = uVar7 | 2;
    }
    if ((-1 < (char)DAT_ram_20001eb4) && (uVar7 == 0)) {
      *pcVar6 = acStack_21[0];
    }
    uVar7 = uVar7 & 0xff;
    uVar4 = 3;
    pcVar6 = DAT_ram_20001eac;
  }
  else {
    if ((DAT_ram_20001e94 & 1) == 0) {
      FUN_ram_0006219c();
      *DAT_ram_20001e88 = *DAT_ram_20001e88 | 0x800000;
      FUN_ram_000628b8();
      uVar4 = 2;
      if (DAT_ram_20001bec == (code *)0x0) {
        gp = 0x20004000;
        return;
      }
LAB_ram_000632de:
      (*DAT_ram_20001bec)(0x81,uVar4);
      gp = 0x20004000;
      return;
    }
    acStack_21[0] = '\0';
    if ((*(uint *)(DAT_ram_20001efc + 0x2c) >> 1 & 1) != 0) {
      uVar7 = DAT_ram_20001eb8 % 64000;
      *(uint *)(DAT_ram_20001efc + 0x44) =
           *(uint *)(DAT_ram_20001efc + 0x44) & 0xfe0fffff |
           (DAT_ram_20001eb8 / 64000 & 0x1f) << 0x14;
      *(uint *)(iVar3 + 0x44) =
           (uVar7 << 10) / 0xfa & 0x3ffff | *(uint *)(iVar3 + 0x44) & 0xfffc0000;
    }
    DAT_ram_20001e94 = 0;
    cVar2 = FUN_ram_20001120(pcVar6,0,acStack_21,0);
    uVar7 = (uint)cVar2;
    if (((uVar7 == 0) && (DAT_ram_20001ed4._3_1_ != -1)) &&
       ((*DAT_ram_20001eac != -1 && (*DAT_ram_20001eac != DAT_ram_20001ed4._3_1_)))) {
      uVar7 = 2;
    }
    if ((char)DAT_ram_20001eb4 < '\0') {
      if (uVar7 != 0) goto LAB_ram_000631de;
    }
    else {
      if (uVar7 != 0) {
LAB_ram_000631de:
        FUN_ram_00062262();
        (*DAT_ram_20001ec4)(3,uVar7 & 0xff,DAT_ram_20001eac);
        if (DAT_ram_20001ed8 != 0) {
          uVar5 = *(undefined1 *)(DAT_ram_20001ed8 + 1);
          iVar3 = DAT_ram_20001ed8 + 2;
          goto LAB_ram_00063208;
        }
LAB_ram_00063422:
        uVar5 = 0;
        iVar3 = 0;
LAB_ram_00063208:
        RF_Rx(iVar3,uVar5,DAT_ram_20001ed4._3_1_,DAT_ram_20001ed4._2_1_);
        gp = 0x20004000;
        return;
      }
      *pcVar6 = acStack_21[0];
    }
    if (((DAT_ram_20001ee0 & 4) != 0) && (pcVar6[(byte)pcVar6[1]] == -0x80)) {
      *DAT_ram_20001ea8 = 0xff;
      DAT_ram_20001eb4 = DAT_ram_20001eb4 | 8;
    }
    puVar1 = DAT_ram_20001e88;
    *DAT_ram_20001e88 = *DAT_ram_20001e88 | 0x800000;
    puVar1[0xb] = puVar1[0xb] & 0xfffffffc;
    FUN_ram_00061f0a((int)(uint)DAT_ram_20001eb4 >> 4 & 3,*(undefined1 *)(DAT_ram_20001ed8 + 1));
    FUN_ram_200010ec();
    FUN_ram_00062262();
    if ((DAT_ram_20001ee0 & 4) != 0) {
      if ((DAT_ram_20001bd2 < '\0') || (3 < DAT_ram_20001ea4)) {
        DAT_ram_20001ea4 = DAT_ram_20001ea4 - 4;
      }
      else {
        DAT_ram_20001ea4 = DAT_ram_20001ea4 + 0xa8bffffc;
      }
      uVar7 = DAT_ram_20001ea4;
      if ((-1 < DAT_ram_20001bd2) && (DAT_ram_20001ea4 < DAT_ram_20001edc)) {
        uVar7 = DAT_ram_20001ea4 + 0xa8c00000;
      }
      uVar7 = uVar7 - DAT_ram_20001edc;
      uVar8 = (uint)(byte)pcVar6[(byte)pcVar6[1] + 1];
      uVar9 = uVar8 * 8;
      if ((char)DAT_ram_20001ee0 < '\0') {
        if (uVar9 < uVar7) {
          uVar7 = uVar7 + uVar8 * -8;
        }
        else {
          uVar7 = uVar9 - uVar7;
        }
        if (uVar7 < 0x21) {
          uVar7 = DAT_ram_20001ea4;
          if ((-1 < DAT_ram_20001bd2) && (DAT_ram_20001ea4 < uVar9)) {
            uVar7 = DAT_ram_20001ea4 + 0xa8c00000;
          }
          DAT_ram_20001edc = uVar7 + uVar8 * -8;
        }
      }
      else {
        uVar7 = DAT_ram_20001ea4;
        if ((-1 < DAT_ram_20001bd2) && (DAT_ram_20001ea4 < uVar9)) {
          uVar7 = DAT_ram_20001ea4 + 0xa8c00000;
        }
        DAT_ram_20001edc = uVar7 + uVar8 * -8;
        DAT_ram_20001ee0 = DAT_ram_20001ee0 | 0x80;
      }
      tmos_set_event(DAT_ram_20001ee4,2);
      if ((DAT_ram_20001eb4 & 8) != 0) {
        if (DAT_ram_20001ed8 == 0) {
          uVar5 = 0;
          iVar3 = 0;
        }
        else {
          uVar5 = *(undefined1 *)(DAT_ram_20001ed8 + 1);
          iVar3 = DAT_ram_20001ed8 + 2;
        }
        RF_Rx(iVar3,uVar5,DAT_ram_20001ed4._3_1_,DAT_ram_20001ed4._2_1_);
        gp = 0x20004000;
        DAT_ram_20001eb4 = DAT_ram_20001eb4 & 0xf7;
        return;
      }
      pcVar6[1] = pcVar6[1] + -2;
    }
    FUN_ram_000628b8();
    (*DAT_ram_20001ec4)(3,0,DAT_ram_20001eac);
    if ((DAT_ram_20001e95 & 1) == 0) {
      DAT_ram_20001e98 = 0;
      uVar7 = 0;
      uVar4 = 0x14;
      pcVar6 = (char *)0x0;
    }
    else {
      DAT_ram_20001e95 = 0;
      uVar7 = 0;
      uVar4 = 4;
      pcVar6 = (char *)0x0;
    }
  }
  (*DAT_ram_20001ec4)(uVar4,uVar7,pcVar6);
  return;
}

