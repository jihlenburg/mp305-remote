/* Address: 000378ca; name: FUN_000378ca; body bytes: 220 */

undefined4 FUN_000378ca(int param_1,uint param_2,uint param_3,undefined4 param_4)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  
  uVar2 = param_3 >> 2;
  if (0x1e < uVar2) {
    uVar2 = 0x1f;
  }
  uVar10 = 1 << (uVar2 & 0xff);
  uVar11 = param_2 & 0xffff;
  uVar3 = ~uVar11 & 0xffff;
  bVar1 = *(byte *)(param_1 + 0x2a);
  uVar12 = param_2 & 0xff0000;
  uVar2 = 0xffffffff;
  iVar5 = param_1;
  for (uVar9 = 0; uVar9 < (*(ushort *)(param_1 + 0x2a) & 0x3ff) >> 4; uVar9 = uVar9 + 1) {
    piVar4 = (int *)(*(int *)(param_1 + 0xc) + uVar9 * 8);
    if (-1 < piVar4[1] << 6) break;
    if ((((-1 < (int)((uint)bVar1 << 0x1c)) &&
         ((*(uint *)(*(int *)(param_1 + 0xc) + uVar9 * 8 + 4) & 0xff0000) == uVar12)) &&
        (iVar8 = *piVar4, (*(uint *)(iVar8 + 4) & uVar10) != 0)) &&
       (iVar8 = FUN_00050abe(iVar8,param_3,param_4,iVar8,uVar3,iVar5,param_2), iVar8 == 1)) {
      return 1;
    }
  }
  do {
    if ((*(ushort *)(param_1 + 0x2a) & 0x3ff) >> 4 <= uVar9) {
      if ((int)uVar2 < 0) {
        uVar6 = 0;
      }
      else {
LAB_0003799a:
        uVar6 = 1;
      }
      return uVar6;
    }
    iVar5 = *(int *)(*(int *)(param_1 + 0xc) + uVar9 * 8);
    if (((((*(uint *)(iVar5 + 4) & uVar10) != 0) &&
         (uVar7 = *(uint *)(*(int *)(param_1 + 0xc) + uVar9 * 8 + 4), (uVar7 & 0xff0000) == uVar12))
        && ((uVar7 = uVar7 & 0xffff, (uVar7 & uVar3) == 0 &&
            (((int)uVar2 < (int)uVar7 && (iVar5 = FUN_00050abe(iVar5,param_3,param_4), iVar5 == 1)))
            ))) && (uVar2 = uVar7, uVar7 == uVar11)) goto LAB_0003799a;
    uVar9 = uVar9 + 1;
  } while( true );
}

