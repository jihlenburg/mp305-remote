/* Address: 00058268; name: FUN_00058268; body bytes: 150 */

void FUN_00058268(uint param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint local_20;
  undefined4 local_1c;
  
  if (DAT_1ffe034c != 0) {
    uVar4 = param_1 / 100;
    uVar3 = param_1 % 100;
    local_20 = param_3;
    local_1c = param_4;
    uVar1 = FUN_0004b9de(DAT_1ffe0354,1);
    FUN_000499de(uVar1,"%02d.%02d V",uVar4,uVar3);
    FUN_000499de(DAT_1ffe057c,"%02d.%02d V",uVar4,uVar3);
    uVar1 = FUN_0004b9de(DAT_1ffe0358,0);
    FUN_000499de(uVar1,"SET : %02d.%02d V",uVar4,uVar3);
    if ((DAT_1fffab03 == '\0') && (DAT_1fffaad6 != '\0')) {
      local_20 = 0;
      local_1c = 0;
      uVar1 = FUN_000491e8(DAT_1ffe03d4);
      FUN_0001050c(&local_20,uVar1);
      iVar2 = FUN_000104f0(&local_20,&DAT_00058338);
      if (iVar2 != 0) {
        local_20 = local_20 & 0xffffff00;
        FUN_00049974(DAT_1ffe03d4,&local_20);
        FUN_000178a4();
      }
    }
    DAT_1fffab74 = (undefined2)param_1;
  }
  return;
}

