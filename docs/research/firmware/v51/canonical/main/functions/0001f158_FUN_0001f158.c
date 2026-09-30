/* Address: 0001f158; name: FUN_0001f158; body bytes: 102 */

void FUN_0001f158(int param_1,int param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = -3;
  if (((param_2 != 0) && (param_3 != 0)) &&
     ((uVar4 = *(uint *)(param_1 + 0xc) & 0x1000, uVar4 == 0 || (uVar4 == 0x1000)))) {
    for (uVar3 = 0; uVar3 < param_3; uVar3 = uVar3 + 1) {
      iVar1 = FUN_0001f1be(param_1,0x80,1,param_4);
      if (iVar1 != 0) {
        return;
      }
      if (uVar4 == 0) {
        uVar2 = (ushort)*(byte *)(param_2 + uVar3);
      }
      else {
        uVar2 = *(ushort *)(param_2 + uVar3 * 2);
      }
      *(ushort *)(param_1 + 4) = uVar2;
      iVar1 = 0;
    }
    if (iVar1 == 0) {
      FUN_0001f1be(param_1,0x40,1,param_4);
      return;
    }
  }
  return;
}

