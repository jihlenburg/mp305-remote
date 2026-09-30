/* Address: 000636d8; name: FUN_000636d8; body bytes: 162 */

/* Recovered from stored Thumb pointer at 0004ed04; callback identification is inferred until
   reviewed. */

void FUN_000636d8(undefined4 *param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  uint uVar7;
  
  piVar4 = (int *)*param_1;
  iVar2 = piVar4[1];
  iVar6 = *piVar4;
  piVar1 = (int *)FUN_0004a118();
  while (piVar1 != (int *)0x0) {
    if ((((piVar1 != piVar4) && (*piVar1 == *piVar4)) && (piVar1[2] == piVar4[2])) &&
       ((char)piVar1[1] == (char)piVar4[1])) {
      return;
    }
    piVar1 = (int *)FUN_0004a13c(&DAT_2003a438);
  }
  uVar7 = 0;
  while( true ) {
    if ((*(ushort *)(iVar6 + 0x2a) & 0x3ff) >> 4 <= uVar7) {
      return;
    }
    uVar3 = *(uint *)(*(int *)(iVar6 + 0xc) + uVar7 * 8 + 4);
    if (((int)(uVar3 << 6) < 0) && ((uVar3 & 0xffffff) == piVar4[2])) break;
    uVar7 = uVar7 + 1;
  }
  FUN_0004a2ac(&DAT_2003a438,piVar4);
  FUN_00046bec(piVar4);
  puVar5 = (undefined4 *)(*(int *)(iVar6 + 0xc) + uVar7 * 8);
  FUN_00050c48(*puVar5,(char)iVar2);
  iVar2 = FUN_00050b0e(*(undefined4 *)(*(int *)(iVar6 + 0xc) + uVar7 * 8));
  if (iVar2 == 0) {
    return;
  }
  FUN_0004e0f6(iVar6,*puVar5,puVar5[1] & 0xffffff);
  return;
}

