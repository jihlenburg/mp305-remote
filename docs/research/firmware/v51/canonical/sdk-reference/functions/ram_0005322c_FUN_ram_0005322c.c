/* Address: ram:0005322c; name: FUN_ram_0005322c; body bytes: 546 */

/* WARNING: Removing unreachable block (ram,0x000532a0) */
/* WARNING: Removing unreachable block (ram,0x0005342c) */
/* WARNING: Removing unreachable block (ram,0x00053388) */

void FUN_ram_0005322c(int param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  gp = 0x20004000;
  FUN_ram_00057e16();
  *(short *)(param_1 + 0x88) = *(short *)(param_1 + 0x88) + 1;
  if (*(char *)(param_1 + 0x7c) == '\x02') {
    *(undefined1 *)(param_1 + 0x7c) = 3;
    *(uint *)(param_1 + 0x54) = *(uint *)(param_1 + 0x54) | 8;
    do {
    } while ((DAT_ram_20001dd5 & 2) == 0);
    DAT_ram_20001dd5 = DAT_ram_20001dd5 & 0xfc;
    iVar2 = (*DAT_ram_20001c00)();
    cVar1 = DAT_ram_20001bd2;
    uVar3 = iVar2 + ((uint)*(ushort *)(param_1 + 0x86) * (uint)DAT_ram_20001b8c + 400) / 800;
    if ((-1 < DAT_ram_20001bd2) && (0xa8bfffff < uVar3)) {
      uVar3 = uVar3 + 0x57400000;
    }
    *(uint *)(param_1 + 0x94) = uVar3;
    uVar5 = (uint)DAT_ram_20001bd5;
    if ((cVar1 < '\0') || (uVar5 <= uVar3)) {
      iVar2 = -uVar5;
    }
    else {
      iVar2 = -0x57400000 - uVar5;
    }
    FUN_ram_0004201e(&LAB_ram_0005344e,param_1,uVar3 + iVar2,param_1 + 0x7d);
  }
  else {
    iVar2 = (*DAT_ram_20001c00)();
    do {
      iVar4 = (*DAT_ram_20001c00)();
    } while (iVar2 == iVar4);
    uVar3 = *(uint *)(param_1 + 0x94);
    uVar5 = (*DAT_ram_20001c00)();
    iVar2 = DAT_ram_20001eb0;
    cVar1 = DAT_ram_20001bd2;
    if ((-1 < DAT_ram_20001bd2) && (uVar3 < uVar5)) {
      uVar3 = uVar3 + 0xa8c00000;
    }
    uVar6 = (uint)DAT_ram_20001b8c;
    uVar3 = uVar3 - uVar5;
    if ((DAT_ram_20001bd5 < uVar3) || (uVar3 == 0)) {
      uVar3 = (*(ushort *)(param_1 + 0x86) * uVar6 + 400) / 800 + *(int *)(param_1 + 0x94);
      if ((-1 < DAT_ram_20001bd2) && (0xa8bfffff < uVar3)) {
        uVar3 = uVar3 + 0x57400000;
      }
      *(uint *)(param_1 + 0x94) = uVar3;
      gp = 0x20004000;
      return;
    }
    DAT_ram_20001dd5 = DAT_ram_20001dd5 | 1;
    *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x8000;
    iVar4 = FUN_ram_0006bae2(uVar3 * 1000000,(int)((ulonglong)uVar3 * 1000000 >> 0x20),uVar6,0);
    *(int *)(iVar2 + 0x6c) = iVar4 << 1;
    do {
    } while ((DAT_ram_20001dd5 & 2) == 0);
    DAT_ram_20001dd5 = DAT_ram_20001dd5 & 0xfc;
    uVar3 = (*(ushort *)(param_1 + 0x86) * uVar6 + 400) / 800 + *(int *)(param_1 + 0x94);
    if ((-1 < cVar1) && (0xa8bfffff < uVar3)) {
      uVar3 = uVar3 + 0x57400000;
    }
    *(uint *)(param_1 + 0x94) = uVar3;
  }
  FUN_ram_00052c2a(param_1);
  FUN_ram_00062262();
  while ((DAT_ram_20001dd4 & 0x10) != 0) {
    do {
    } while ((DAT_ram_20001dd4 & 0x20) == 0);
    DAT_ram_20001dd4 = DAT_ram_20001dd4 & 0xcf;
    FUN_ram_0005301a(param_1);
  }
  return;
}

