/* Address: ram:0004fb2e; name: FUN_ram_0004fb2e; body bytes: 1030 */

int FUN_ram_0004fb2e(undefined1 *param_1,int param_2,undefined2 *param_3)

{
  short *psVar1;
  char cVar2;
  undefined1 uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  ushort uVar7;
  short *psVar8;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [28];
  
  gp = 0x20004000;
  psVar1 = *(short **)(param_1 + 0x34);
  if (psVar1 == (short *)0x0) {
    if (param_2 != 0xb) {
      gp = 0x20004000;
      return 0;
    }
    FUN_ram_0004472c(*param_1,*(undefined2 *)(param_1 + 2),param_1 + 6,*(undefined1 *)param_3);
    gp = 0x20004000;
    return 0;
  }
  if (*psVar1 != *(short *)(param_1 + 2)) {
    gp = 0x20004000;
    return 8;
  }
  if ((char)psVar1[1] == '\0') {
LAB_ram_0004fb5e:
    gp = 0x20004000;
    return 7;
  }
  switch(param_2 - 2U & 0xff) {
  case 0:
    iVar4 = FUN_ram_0004f5d2(psVar1,param_3);
    gp = 0x20004000;
    return iVar4;
  case 1:
    tmos_memcpy(psVar1 + 0x26,param_3,0x10);
    iVar6 = FUN_ram_000502a6(psVar1);
    iVar4 = 0;
    if (iVar6 != 0) {
      iVar4 = 8;
    }
    if (*(char *)((int)psVar1 + 3) == 'T') {
      uVar3 = 0x59;
    }
    else if (*(char *)((int)psVar1 + 3) == 'V') {
      uVar3 = 0x5a;
    }
    else {
      uVar3 = 0x14;
    }
    goto LAB_ram_0004fbc2;
  case 2:
    psVar8 = psVar1 + 0x2e;
    tmos_memcpy(psVar8,param_3,0x10);
    iVar4 = *(int *)(psVar1 + 0x40);
    if (iVar4 == 0) {
      FUN_ram_0004e8ec(psVar1,psVar1 + 4,psVar8,auStack_30);
      iVar4 = tmos_memcmp(auStack_30,psVar1 + 0x26,0x10);
      if (iVar4 == 0) {
        gp = 0x20004000;
        return param_2;
      }
      iVar4 = FUN_ram_00051502(psVar1 + 4,psVar8,psVar1 + 0x1e,auStack_40);
      if (iVar4 == 0) {
        uVar5 = FUN_ram_0004e9a0(psVar1);
        iVar6 = (*DAT_ram_20001d48)(*psVar1,auStack_40,0,0,uVar5,DAT_ram_20001d48);
        iVar4 = 0;
        if (iVar6 != 0) goto LAB_ram_0004fcf8;
      }
      else {
LAB_ram_0004fcf8:
        iVar4 = 8;
      }
      uVar3 = 0x22;
      goto LAB_ram_0004fbc2;
    }
    cVar2 = *(char *)((int)psVar1 + 3);
    if (cVar2 != 'Y') {
      if (cVar2 == 'Z') {
        if (DAT_ram_20001f04 == 0) {
          gp = 0x20004000;
          return 8;
        }
        if (*(code **)(DAT_ram_20001f04 + 8) == (code *)0x0) {
          gp = 0x20004000;
          return 8;
        }
        cVar2 = (**(code **)(DAT_ram_20001f04 + 8))
                          (iVar4 + 0x40,iVar4 + 0x80,psVar8,
                           (int)(uint)*(byte *)((int)psVar1 + (*(byte *)((int)psVar1 + 7) >> 3) + 8)
                           >> (*(byte *)((int)psVar1 + 7) & 7) & 1U | 0x80,auStack_30);
        if (cVar2 != '\0') {
          gp = 0x20004000;
          return 8;
        }
        tmos_memcmp(psVar1 + 0x26,auStack_30,0x10);
        cVar2 = *(char *)((int)psVar1 + 7);
        *(char *)((int)psVar1 + 7) = cVar2 + '\x01';
        iVar4 = 0;
        if ((byte)(cVar2 + 1U) < 0x14) {
          tmos_set_event(DAT_ram_20001d4f,1);
          uVar3 = 0x55;
        }
        else {
          FUN_ram_0005033c(psVar1);
          uVar3 = 0x5e;
        }
        goto LAB_ram_0004fbc2;
      }
      if (cVar2 != '\\') {
        gp = 0x20004000;
        return 0;
      }
    }
    FUN_ram_0005033c(psVar1);
    uVar3 = 0x5e;
    break;
  case 3:
    FUN_ram_0004e5a2(*(short *)(param_1 + 2),*(undefined1 *)param_3);
    gp = 0x20004000;
    return 0;
  case 4:
    if (*(char *)((int)psVar1 + 3) != '\"') {
      gp = 0x20004000;
      return 7;
    }
    if (*(int *)(psVar1 + 0x3a) == 0) {
      uVar5 = FUN_ram_20000040(0x1c,0x53);
      *(undefined4 *)(psVar1 + 0x3a) = uVar5;
    }
    if (*(int *)(psVar1 + 0x3a) == 0) {
      gp = 0x20004000;
      return 7;
    }
    tmos_memcpy(*(int *)(psVar1 + 0x3a),param_3,0x10);
    iVar4 = *(int *)(psVar1 + 0x3a);
    uVar3 = FUN_ram_0004e9a0(psVar1);
    *(undefined1 *)(iVar4 + 0x1a) = uVar3;
    uVar3 = 0x23;
    break;
  case 5:
    if (*(char *)((int)psVar1 + 3) != '#') {
      gp = 0x20004000;
      return 7;
    }
    iVar4 = *(int *)(psVar1 + 0x3a);
    *(undefined2 *)(iVar4 + 0x10) = *param_3;
    tmos_memcpy(iVar4 + 0x12,param_3 + 1,8);
    uVar7 = *(ushort *)(*(int *)(psVar1 + 0x36) + 0x14);
    if (((uVar7 & 2) == 0) || ((*(ushort *)(*(int *)(psVar1 + 0x14) + 4) & 2) == 0))
    goto LAB_ram_0004fdea;
    uVar3 = 0x24;
    break;
  case 6:
    if (*(char *)((int)psVar1 + 3) != '$') {
      gp = 0x20004000;
      return 7;
    }
    if (*(int *)(psVar1 + 0x3c) == 0) {
      uVar5 = FUN_ram_20000040(0x16,1);
      *(undefined4 *)(psVar1 + 0x3c) = uVar5;
    }
    if (*(int *)(psVar1 + 0x3c) == 0) {
      gp = 0x20004000;
      return 0;
    }
    tmos_memcpy(*(int *)(psVar1 + 0x3c),param_3,0x10);
    uVar3 = 0x25;
    break;
  case 7:
    if (*(char *)((int)psVar1 + 3) != '%') {
      gp = 0x20004000;
      return 7;
    }
    tmos_memcpy(*(int *)(psVar1 + 0x3c) + 0x10,(undefined1 *)((int)param_3 + 1),6);
    uVar7 = *(ushort *)(*(int *)(psVar1 + 0x36) + 0x14);
LAB_ram_0004fdea:
    if (((uVar7 & 4) == 0) || ((*(ushort *)(*(int *)(psVar1 + 0x14) + 4) & 4) == 0)) {
LAB_ram_0004fe2a:
      FUN_ram_0004faa6(param_1);
      gp = 0x20004000;
      return 0;
    }
    uVar3 = 0x26;
    break;
  case 8:
    if (*(int *)(psVar1 + 0x3e) == 0) {
      uVar5 = FUN_ram_20000040(0x14,0x53);
      *(undefined4 *)(psVar1 + 0x3e) = uVar5;
    }
    if (*(int *)(psVar1 + 0x3e) == 0) {
      gp = 0x20004000;
      return 8;
    }
    tmos_memcpy(*(int *)(psVar1 + 0x3e),param_3,0x10);
    *(undefined4 *)(*(int *)(psVar1 + 0x3e) + 0x10) = 0xffffffff;
    goto LAB_ram_0004fe2a;
  case 9:
    goto switchD_ram_0004fb8a_caseD_9;
  case 10:
    tmos_memcpy(*(int *)(psVar1 + 0x40) + 0x40,param_3,0x40);
    FUN_ram_0004e8b0(psVar1);
    cVar2 = *(char *)((int)psVar1 + 3);
    if (cVar2 == 'P') {
      uVar3 = 0x54;
    }
    else if (cVar2 == 'Q') {
      tmos_set_event(DAT_ram_20001d4f,1);
      uVar3 = 0x55;
    }
    else {
      if (cVar2 != 'R') {
        gp = 0x20004000;
        return 0;
      }
      if (DAT_ram_20001f04 == 0) {
        gp = 0x20004000;
        return 8;
      }
      if (*(code **)(DAT_ram_20001f04 + 8) == (code *)0x0) {
        gp = 0x20004000;
        return 8;
      }
      (**(code **)(DAT_ram_20001f04 + 8))
                (*(int *)(psVar1 + 0x40) + 0x80,*(int *)(psVar1 + 0x40) + 0x80,psVar1 + 4,0,
                 auStack_30);
      FUN_ram_00044ef0(*psVar1,psVar1 + 4,auStack_30);
      uVar3 = 0x5b;
    }
    break;
  case 0xb:
    if (*(char *)((int)psVar1 + 3) != '^') {
      gp = 0x20004000;
      return 7;
    }
    iVar4 = tmos_memcmp(param_3,*(undefined4 *)(psVar1 + 0x40),0x10);
    if (iVar4 == 0) {
      gp = 0x20004000;
      return 0xb;
    }
    tmos_memcpy(*(undefined4 *)(psVar1 + 0x40),param_3,0x10);
    uVar5 = FUN_ram_0004e9a0(psVar1);
    iVar6 = (*DAT_ram_20001d48)(*psVar1,*(undefined4 *)(psVar1 + 0x38),0,0,uVar5,DAT_ram_20001d48);
    iVar4 = 0;
    if (iVar6 != 0) {
      iVar4 = 8;
    }
    uVar3 = 0x21;
LAB_ram_0004fbc2:
    *(undefined1 *)((int)psVar1 + 3) = uVar3;
    gp = 0x20004000;
    return iVar4;
  default:
    goto LAB_ram_0004fb5e;
  }
  *(undefined1 *)((int)psVar1 + 3) = uVar3;
switchD_ram_0004fb8a_caseD_9:
  return 0;
}

