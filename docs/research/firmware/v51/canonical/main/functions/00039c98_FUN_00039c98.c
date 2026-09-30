/* Address: 00039c98; name: FUN_00039c98; body bytes: 276 */

void FUN_00039c98(int param_1)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  if ((*(int *)(param_1 + 0x70) == 0) && ((*(byte *)(param_1 + 0x99) & 1) == 0)) {
    for (iVar7 = *(int *)(param_1 + 0x68); iVar7 != 0; iVar7 = FUN_0004bc8c(iVar7)) {
      iVar3 = FUN_0004cd84(iVar7,0x8000);
      if (iVar3 == 0) {
        iVar4 = *(int *)(param_1 + 0x48);
        iVar3 = iVar4;
        if (iVar4 < 1) {
          iVar3 = -iVar4;
        }
        if (iVar3 < (int)(uint)*(byte *)(DAT_2003a470 + 0x26)) {
          iVar3 = *(int *)(param_1 + 0x4c);
          if (iVar3 < 1) {
            iVar3 = -iVar3;
          }
          if (iVar3 < (int)(uint)*(byte *)(DAT_2003a470 + 0x26)) {
            *(undefined4 *)(param_1 + 0x8c) = 0;
            *(undefined4 *)(param_1 + 0x90) = 0;
          }
        }
        iVar4 = iVar4 + *(int *)(param_1 + 0x8c);
        *(int *)(param_1 + 0x8c) = iVar4;
        iVar5 = *(int *)(param_1 + 0x90) + *(int *)(param_1 + 0x4c);
        *(int *)(param_1 + 0x90) = iVar5;
        iVar3 = iVar4;
        if (iVar4 < 1) {
          iVar3 = -iVar4;
        }
        if (iVar3 <= (int)(uint)*(byte *)(DAT_2003a470 + 0x27)) {
          iVar3 = iVar5;
          if (iVar5 < 1) {
            iVar3 = -iVar5;
          }
          if (iVar3 <= (int)(uint)*(byte *)(DAT_2003a470 + 0x27)) {
            return;
          }
        }
        *(byte *)(param_1 + 0x99) = *(byte *)(param_1 + 0x99) | 1;
        iVar3 = iVar4;
        if (iVar4 < 1) {
          iVar3 = -iVar4;
        }
        iVar6 = iVar5;
        if (iVar5 < 1) {
          iVar6 = -iVar5;
        }
        if (iVar6 < iVar3) {
          bVar1 = *(byte *)(param_1 + 0x98) & 0xf;
          if (iVar4 < 1) {
            cVar2 = bVar1 + 0x10;
          }
          else {
            cVar2 = bVar1 + 0x20;
          }
        }
        else {
          bVar1 = *(byte *)(param_1 + 0x98) & 0xf;
          if (iVar5 < 1) {
            cVar2 = bVar1 + 0x40;
          }
          else {
            cVar2 = bVar1 + 0x80;
          }
        }
        *(char *)(param_1 + 0x98) = cVar2;
        FUN_0004e5a6(iVar7,0xd,DAT_2003a470);
        iVar3 = FUN_0003a5c8(param_1);
        if (iVar3 != 0) {
          return;
        }
        FUN_0004883e(DAT_2003a470,0xd,iVar7);
        FUN_0003a5c8(DAT_2003a470);
        return;
      }
    }
  }
  return;
}

