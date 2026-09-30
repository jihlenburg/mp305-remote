/* Address: 000569b8; name: FUN_000569b8; body bytes: 230 */

void FUN_000569b8(uint param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 extraout_s1;
  undefined8 uVar5;
  uint local_20;
  undefined4 local_1c;
  
  if (DAT_1ffe034c != 0) {
    uVar4 = param_1 / 1000;
    uVar3 = param_1 % 1000;
    local_20 = param_3;
    local_1c = param_4;
    uVar1 = FUN_0004b9de(DAT_1ffe0364,1);
    FUN_000499de(uVar1,"%01d.%03d A",uVar4,uVar3);
    FUN_000499de(DAT_1ffe0580,"%01d.%03d A",uVar4,uVar3);
    uVar5 = FUN_00010a20(param_1);
    uVar1 = FUN_00010920((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),0,0x40240000);
    uVar1 = FUN_00020198(uVar1);
    DAT_1fffab72 = FUN_00010a90(uVar1,extraout_s1);
    FUN_000499de(DAT_1ffe0568,"%d.%02d",DAT_1fffab72 / 100,(uint)DAT_1fffab72 % 100);
    FUN_0003fa48(DAT_1ffe0570,0,0,param_1);
    uVar1 = FUN_0004b9de(DAT_1ffe0368,0);
    FUN_000499de(uVar1,"SET : %01d.%03d A",uVar4,uVar3);
    if ((DAT_1fffab04 == '\0') && (DAT_1fffaad7 != '\0')) {
      local_20 = 0;
      local_1c = 0;
      uVar1 = FUN_000491e8(DAT_1ffe03d4);
      FUN_0001050c(&local_20,uVar1);
      iVar2 = FUN_000104f0(&local_20,&LAB_00056af0);
      if (iVar2 != 0) {
        local_20 = local_20 & 0xffffff00;
        FUN_00049974(DAT_1ffe03d4,&local_20);
        FUN_000178a4();
      }
    }
    DAT_1fffab76 = (undefined2)param_1;
  }
  return;
}

