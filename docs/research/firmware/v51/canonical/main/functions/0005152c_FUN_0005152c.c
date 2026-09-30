/* Address: 0005152c; name: FUN_0005152c; body bytes: 186 */

void FUN_0005152c(int param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar1 = FUN_0005150c();
  uVar2 = FUN_00051512(param_1);
  uVar3 = FUN_00051518(param_1);
  if (uVar3 <= param_2) {
    param_2 = uVar3 - 1;
  }
  FUN_0004ef90(param_1);
  if (iVar1 != 0) {
    if ((*(byte *)(param_1 + 0x30) & 0xc) == 0) {
      iVar4 = FUN_0004c924(iVar1,0,0x14);
      iVar5 = FUN_0004baf8(iVar1);
      FUN_0004e538(iVar1,param_2 * (iVar4 + iVar5),param_3);
    }
    else {
      iVar4 = FUN_0004c924(iVar1,0,0x15);
      iVar5 = FUN_0004bb1a(iVar1);
      iVar6 = FUN_0004c5e2(param_1,0);
      if (iVar6 == 1) {
        iVar4 = -param_2 * (iVar4 + iVar5);
      }
      else {
        iVar4 = param_2 * (iVar4 + iVar5);
      }
      FUN_0004e510(iVar1,iVar4,param_3);
    }
    uVar3 = 0;
    while (iVar1 = FUN_0004ba04(uVar2,uVar3,&DAT_0007a5bc), iVar1 != 0) {
      FUN_0004e860(iVar1,1,uVar3 == param_2);
      uVar3 = uVar3 + 1;
    }
    *(uint *)(param_1 + 0x2c) = param_2;
  }
  return;
}

