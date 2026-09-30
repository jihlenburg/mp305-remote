/* Address: ram:00056062; name: FUN_ram_00056062; body bytes: 380 */

/* WARNING: Removing unreachable block (ram,0x000560b2) */
/* WARNING: Removing unreachable block (ram,0x000561b0) */

void FUN_ram_00056062(int param_1)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  uint uVar10;
  uint uVar11;
  
  cVar1 = DAT_ram_20001bd2;
  gp = 0x20004000;
  uVar11 = (uint)DAT_ram_20001b8c;
  iVar8 = *(ushort *)(param_1 + 0x36) + 1;
  if (DAT_ram_20001e04 < 2) {
    uVar11 = (((*(byte *)(param_1 + 0x35) < 2 ^ 1) + iVar8) * uVar11 + 400) / 800 +
             *(int *)(param_1 + 0x88);
    if ((-1 < DAT_ram_20001bd2) && (0xa8bfffff < uVar11)) {
      uVar11 = uVar11 + 0x57400000;
    }
    *(uint *)(param_1 + 0x90) = uVar11;
  }
  else {
    uVar2 = (iVar8 * uVar11 + 400) / 800 + *(int *)(param_1 + 0x88);
    if ((-1 < DAT_ram_20001bd2) && (0xa8bfffff < uVar2)) {
      uVar2 = uVar2 + 0x57400000;
    }
    *(uint *)(param_1 + 0x90) = uVar2;
    iVar8 = (uint)*(ushort *)(param_1 + 0x1c6) + (uint)*(ushort *)(param_1 + 0x1ca) + 0x271;
    uVar3 = FUN_ram_0006bae2(uVar11 * iVar8,(int)((longlong)iVar8 * (ulonglong)uVar11 >> 0x20),
                             1000000,0);
    iVar8 = DAT_ram_20001df0;
    uVar10 = 0;
    do {
      uVar4 = uVar11 * uVar10 + 800;
      iVar5 = FUN_ram_0006bae2(uVar4,(int)((ulonglong)uVar11 * (ulonglong)uVar10 >> 0x20) +
                                     (uint)(uVar4 < uVar11 * uVar10),0x640,0);
      uVar4 = iVar5 + uVar2;
      uVar7 = 0xffffffff;
      piVar9 = (int *)iVar8;
      while( true ) {
        if ((piVar9 == (int *)0x0) ||
           ((piVar9 == (int *)param_1 && (piVar9 = (int *)*piVar9, piVar9 == (int *)0x0))))
        goto LAB_ram_00056122;
        if (piVar9[0x23] == *(int *)(param_1 + 0x8c)) {
          uVar6 = piVar9[0x24];
          uVar7 = uVar6 - uVar4;
          if (uVar6 <= uVar4) {
            uVar7 = uVar4 - uVar6;
          }
        }
        if (uVar7 < uVar3) break;
        piVar9 = (int *)*piVar9;
      }
      uVar10 = uVar10 + 1;
    } while (uVar10 < (uint)*(byte *)(param_1 + 0x35) * 2 - 1);
LAB_ram_00056122:
    uVar3 = uVar11 * uVar10 + 800;
    iVar8 = FUN_ram_0006bae2(uVar3,(uint)(uVar3 < uVar11 * uVar10) +
                                   (int)((ulonglong)uVar11 * (ulonglong)uVar10 >> 0x20),0x640,0);
    uVar2 = iVar8 + uVar2;
    if ((-1 < cVar1) && (0xa8bfffff < uVar2)) {
      uVar2 = uVar2 + 0x57400000;
    }
    *(uint *)(param_1 + 0x90) = uVar2;
  }
  return;
}

