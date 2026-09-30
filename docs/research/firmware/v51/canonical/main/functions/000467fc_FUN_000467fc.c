/* Address: 000467fc; name: FUN_000467fc; body bytes: 100 */

undefined4 FUN_000467fc(int param_1,int param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  uint uVar5;
  
  if (param_1 != 0) {
    iVar1 = FUN_0003de3c();
    uVar2 = FUN_0003df08(param_1);
    for (uVar5 = 0; uVar5 < uVar2; uVar5 = uVar5 + 1) {
      piVar3 = *(int **)(iVar1 + uVar5 * 4);
      if (((*piVar3 != 0) && ((piVar3[2] & 0xffffU) >> 0xf == param_3)) &&
         ((uVar4 = piVar3[2] & 0x7fff, uVar4 == 0 || (*(ushort *)(param_2 + 8) == uVar4)))) {
        *(int *)(param_2 + 0xc) = piVar3[1];
        (*(code *)**(undefined4 **)(iVar1 + uVar5 * 4))(param_2);
        if ((int)((uint)*(byte *)(param_2 + 0x18) << 0x1e) < 0) {
          return 1;
        }
        if ((*(byte *)(param_2 + 0x18) & 1) != 0) {
          return 0;
        }
      }
    }
  }
  return 1;
}

