/* Address: 0005d8ec; name: FUN_0005d8ec; body bytes: 132 */

void FUN_0005d8ec(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  uVar7 = *(undefined4 *)(param_1 + 0x40);
  uVar6 = *(undefined4 *)(param_1 + 0x44);
  uVar5 = *(ushort *)(param_1 + 0x48) & 0x7fff;
  for (uVar4 = 0; uVar4 < uVar5; uVar4 = uVar4 + 1) {
    uVar1 = (*(uint *)(param_1 + 0x48) & 0x3fffffff) >> 0xf;
    uVar1 = (uint)(uVar4 == uVar1 * (uVar4 / uVar1));
    iVar2 = FUN_0004a388(uVar4,0,uVar5 - 1,uVar7,uVar6);
    iVar3 = FUN_0004a14a();
    while (iVar3 != 0) {
      if ((*(int *)(iVar3 + 0xc) <= iVar2) && (iVar2 <= *(int *)(iVar3 + 0x10))) {
        if (*(int *)(iVar3 + 0x14) == 0xff) {
          *(uint *)(iVar3 + 0x1c) = uVar1;
          *(uint *)(iVar3 + 0x14) = uVar4;
        }
        if (*(uint *)(iVar3 + 0x14) != uVar4) {
          *(uint *)(iVar3 + 0x20) = uVar1;
          *(uint *)(iVar3 + 0x18) = uVar4;
        }
      }
      iVar3 = FUN_0004a144(param_1 + 0x2c);
    }
  }
  return;
}

