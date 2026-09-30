/* Address: ram:0006bae2; name: FUN_ram_0006bae2; body bytes: 920 */

/* WARNING: Removing unreachable block (ram,0x0006bba4) */

ulonglong FUN_ram_0006bae2(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  gp = 0x20004000;
  if (param_4 == 0) {
    if (param_3 <= param_2) {
      if (param_3 == 0) {
        param_3 = 0xffffffff;
      }
      if (param_3 < 0x10000) {
        iVar4 = 0;
        uVar2 = param_3;
        if (0xff < param_3) {
          uVar2 = param_3 >> 8;
          iVar4 = 8;
        }
      }
      else if (param_3 < 0x1000000) {
        iVar4 = 0x10;
        uVar2 = param_3 >> 0x10;
      }
      else {
        iVar4 = 0x18;
        uVar2 = param_3 >> 0x18;
      }
      uVar2 = (uint)(byte)(&DAT_ram_0006c530)[uVar2] + iVar4;
      uVar3 = 0x20 - uVar2;
      if (uVar3 == 0) {
        param_2 = param_2 - param_3;
        uVar1 = param_3 >> 0x10;
        uVar9 = param_3 & 0xffff;
        uVar2 = 1;
      }
      else {
        param_3 = param_3 << (uVar3 & 0x1f);
        uVar5 = param_2 >> (uVar2 & 0x1f);
        uVar1 = param_3 >> 0x10;
        if (uVar1 == 0) {
          uVar7 = 0xffffffff;
        }
        else {
          uVar7 = uVar5 / uVar1;
        }
        uVar2 = param_2 << (uVar3 & 0x1f) | param_1 >> (uVar2 & 0x1f);
        uVar9 = param_3 & 0xffff;
        param_1 = param_1 << (uVar3 & 0x1f);
        if (uVar1 != 0) {
          uVar5 = uVar5 % uVar1;
        }
        uVar6 = uVar9 * uVar7;
        uVar5 = uVar5 << 0x10 | uVar2 >> 0x10;
        uVar3 = uVar7;
        if (uVar5 < uVar6) {
          uVar5 = uVar5 + param_3;
          uVar3 = uVar7 - 1;
          if ((param_3 <= uVar5) && (uVar5 < uVar6)) {
            uVar3 = uVar7 - 2;
            uVar5 = uVar5 + param_3;
          }
        }
        uVar5 = uVar5 - uVar6;
        if (uVar1 == 0) {
          uVar7 = 0xffffffff;
        }
        else {
          uVar7 = uVar5 / uVar1;
        }
        if (uVar1 != 0) {
          uVar5 = uVar5 % uVar1;
        }
        uVar6 = uVar9 * uVar7;
        param_2 = uVar5 << 0x10 | uVar2 & 0xffff;
        uVar2 = uVar7;
        if (param_2 < uVar6) {
          param_2 = param_2 + param_3;
          uVar2 = uVar7 - 1;
          if ((param_3 <= param_2) && (param_2 < uVar6)) {
            uVar2 = uVar7 - 2;
            param_2 = param_2 + param_3;
          }
        }
        param_2 = param_2 - uVar6;
        uVar2 = uVar3 << 0x10 | uVar2;
      }
      if (uVar1 == 0) {
        uVar3 = 0xffffffff;
      }
      else {
        uVar3 = param_2 / uVar1;
        param_2 = param_2 % uVar1;
      }
      uVar7 = uVar3 * uVar9;
      uVar6 = param_1 >> 0x10 | param_2 << 0x10;
      uVar5 = uVar3;
      if (uVar6 < uVar7) {
        uVar6 = uVar6 + param_3;
        uVar5 = uVar3 - 1;
        if ((param_3 <= uVar6) && (uVar6 < uVar7)) {
          uVar5 = uVar3 - 2;
          uVar6 = uVar6 + param_3;
        }
      }
      uVar6 = uVar6 - uVar7;
      if (uVar1 == 0) {
        uVar3 = 0xffffffff;
      }
      else {
        uVar3 = uVar6 / uVar1;
      }
      if (uVar1 != 0) {
        uVar6 = uVar6 % uVar1;
      }
      uVar7 = uVar6 << 0x10 | param_1 & 0xffff;
      uVar1 = uVar3;
      if (uVar7 < uVar3 * uVar9) {
        uVar7 = uVar7 + param_3;
        if ((uVar7 < param_3) || (uVar1 = uVar3 - 2, uVar3 * uVar9 <= uVar7)) {
          uVar1 = uVar3 - 1;
        }
      }
      return CONCAT44(uVar2,uVar5 << 0x10 | uVar1);
    }
    if (param_3 < 0x10000) {
      iVar4 = 0;
      uVar2 = param_3;
      if (0xff < param_3) {
        uVar2 = param_3 >> 8;
        iVar4 = 8;
      }
    }
    else if (param_3 < 0x1000000) {
      iVar4 = 0x10;
      uVar2 = param_3 >> 0x10;
    }
    else {
      iVar4 = 0x18;
      uVar2 = param_3 >> 0x18;
    }
    uVar3 = 0x20 - (iVar4 + (uint)(byte)(&DAT_ram_0006c530)[uVar2]);
    if (uVar3 != 0) {
      param_3 = param_3 << (uVar3 & 0x1f);
      param_2 = param_1 >> (iVar4 + (uint)(byte)(&DAT_ram_0006c530)[uVar2] & 0x1f) |
                param_2 << (uVar3 & 0x1f);
      param_1 = param_1 << (uVar3 & 0x1f);
    }
    uVar2 = param_3 >> 0x10;
    if (uVar2 == 0) {
      uVar3 = 0xffffffff;
    }
    else {
      uVar3 = param_2 / uVar2;
    }
    if (uVar2 != 0) {
      param_2 = param_2 % uVar2;
    }
    uVar1 = (param_3 & 0xffff) * uVar3;
    uVar7 = param_2 << 0x10 | param_1 >> 0x10;
    uVar5 = uVar3;
    if (uVar7 < uVar1) {
      uVar7 = uVar7 + param_3;
      uVar5 = uVar3 - 1;
      if ((param_3 <= uVar7) && (uVar7 < uVar1)) {
        uVar5 = uVar3 - 2;
        uVar7 = uVar7 + param_3;
      }
    }
    uVar7 = uVar7 - uVar1;
    if (uVar2 == 0) {
      uVar3 = 0xffffffff;
    }
    else {
      uVar3 = uVar7 / uVar2;
    }
    if (uVar2 != 0) {
      uVar7 = uVar7 % uVar2;
    }
    uVar1 = (param_3 & 0xffff) * uVar3;
    uVar7 = uVar7 << 0x10 | param_1 & 0xffff;
    uVar2 = uVar3;
    if (uVar7 < uVar1) {
      uVar7 = uVar7 + param_3;
      if ((uVar7 < param_3) || (uVar2 = uVar3 - 2, uVar1 <= uVar7)) {
        uVar2 = uVar3 - 1;
      }
    }
    return (ulonglong)(uVar5 << 0x10 | uVar2);
  }
  if (param_2 < param_4) {
    return 0;
  }
  if (param_4 < 0x10000) {
    if (param_4 < 0x100) {
      iVar4 = 0;
      uVar2 = param_4;
    }
    else {
      iVar4 = 8;
      uVar2 = param_4 >> 8;
    }
  }
  else if (param_4 < 0x1000000) {
    iVar4 = 0x10;
    uVar2 = param_4 >> 0x10;
  }
  else {
    iVar4 = 0x18;
    uVar2 = param_4 >> 0x18;
  }
  uVar2 = (uint)(byte)(&DAT_ram_0006c530)[uVar2] + iVar4;
  uVar3 = 0x20 - uVar2;
  if (uVar3 == 0) {
    if (param_4 < param_2) {
      return 1;
    }
    return (ulonglong)(param_1 < param_3 ^ 1);
  }
  uVar1 = param_4 << (uVar3 & 0x1f) | param_3 >> (uVar2 & 0x1f);
  uVar5 = param_2 >> (uVar2 & 0x1f);
  uVar7 = uVar1 >> 0x10;
  if (uVar7 == 0) {
    uVar9 = 0xffffffff;
  }
  else {
    uVar9 = uVar5 / uVar7;
  }
  uVar2 = param_1 >> (uVar2 & 0x1f) | param_2 << (uVar3 & 0x1f);
  param_3 = param_3 << (uVar3 & 0x1f);
  if (uVar7 != 0) {
    uVar5 = uVar5 % uVar7;
  }
  uVar6 = (uVar1 & 0xffff) * uVar9;
  uVar8 = uVar5 << 0x10 | uVar2 >> 0x10;
  uVar5 = uVar9;
  if (uVar8 < uVar6) {
    uVar8 = uVar8 + uVar1;
    uVar5 = uVar9 - 1;
    if ((uVar1 <= uVar8) && (uVar8 < uVar6)) {
      uVar5 = uVar9 - 2;
      uVar8 = uVar8 + uVar1;
    }
  }
  uVar8 = uVar8 - uVar6;
  if (uVar7 == 0) {
    uVar9 = 0xffffffff;
  }
  else {
    uVar9 = uVar8 / uVar7;
  }
  if (uVar7 != 0) {
    uVar8 = uVar8 % uVar7;
  }
  uVar7 = (uVar1 & 0xffff) * uVar9;
  uVar6 = uVar8 << 0x10 | uVar2 & 0xffff;
  uVar2 = uVar9;
  if (uVar6 < uVar7) {
    uVar6 = uVar6 + uVar1;
    uVar2 = uVar9 - 1;
    if ((uVar1 <= uVar6) && (uVar6 < uVar7)) {
      uVar2 = uVar9 - 2;
      uVar6 = uVar6 + uVar1;
    }
  }
  uVar1 = uVar5 << 0x10 | uVar2;
  uVar5 = param_3 & 0xffff;
  param_3 = param_3 >> 0x10;
  uVar9 = (uVar2 & 0xffff) * uVar5;
  uVar5 = (uVar1 >> 0x10) * uVar5;
  uVar2 = (uVar2 & 0xffff) * param_3 + uVar5 + (uVar9 >> 0x10);
  iVar4 = (uVar1 >> 0x10) * param_3;
  if (uVar2 < uVar5) {
    iVar4 = iVar4 + 0x10000;
  }
  uVar5 = iVar4 + (uVar2 >> 0x10);
  if ((uVar5 <= uVar6 - uVar7) &&
     ((uVar6 - uVar7 != uVar5 || (uVar2 * 0x10000 + (uVar9 & 0xffff) <= param_1 << (uVar3 & 0x1f))))
     ) {
    return (ulonglong)uVar1;
  }
  return (ulonglong)(uVar1 - 1);
}

