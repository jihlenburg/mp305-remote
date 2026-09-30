/* Address: 000637cc; name: FUN_000637cc; body bytes: 164 */

undefined4 FUN_000637cc(int param_1,uint param_2,uint param_3,int *param_4)

{
  int *piVar1;
  uint uVar2;
  int *piVar3;
  undefined4 uVar4;
  uint uVar5;
  
  uVar4 = 0;
  piVar1 = (int *)FUN_0004a14a();
  while ((piVar3 = piVar1, piVar3 != (int *)0x0 && (piVar3 != param_4))) {
    piVar1 = (int *)FUN_0004a144(&DAT_2003a438,piVar3);
    if (((*piVar3 == param_1) && ((piVar3[2] == param_2 || (param_2 == 0xf0000)))) &&
       ((*(byte *)(piVar3 + 1) == param_3 || (param_3 == 0xff)))) {
      for (uVar5 = 0; uVar5 < (*(ushort *)(param_1 + 0x2a) & 0x3ff) >> 4; uVar5 = uVar5 + 1) {
        uVar2 = *(uint *)(*(int *)(param_1 + 0xc) + uVar5 * 8 + 4);
        if (((int)(uVar2 << 6) < 0) && ((param_2 == 0xf0000 || ((uVar2 & 0xffffff) == param_2)))) {
          FUN_00050c48(*(undefined4 *)(*(int *)(param_1 + 0xc) + uVar5 * 8),(char)piVar3[1]);
        }
      }
      FUN_0003c97c(piVar3,0);
      FUN_0004a2ac(&DAT_2003a438,piVar3);
      FUN_00046bec(piVar3);
      uVar4 = 1;
    }
  }
  return uVar4;
}

