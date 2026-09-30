/* Address: 00025cb8; name: FUN_00025cb8; body bytes: 242 */

void FUN_00025cb8(int param_1,undefined4 *param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  
  iVar2 = FUN_0004b9de(param_1,0);
  if (iVar2 != 0) {
    FUN_000261ec(param_1,param_2);
    FUN_00025dac(param_1,param_2);
    uVar3 = FUN_0004c83a(param_1,0);
    uVar4 = FUN_0004c8d6(param_1,0);
    iVar2 = FUN_0004c5fa(param_1,0);
    iVar5 = FUN_0004cbf6(param_1,0);
    iVar6 = FUN_0004c6de(param_1,0);
    if ((iVar5 == 0x3fffffff) && (-1 < (int)((uint)*(ushort *)(param_1 + 0x2a) << 0x14))) {
      uVar7 = 1;
    }
    else {
      uVar7 = 0;
    }
    uVar8 = FUN_0004bb1a(param_1);
    uVar1 = FUN_0004c924(param_1,0,0x82);
    uVar3 = FUN_00037f14(uVar8,uVar7,uVar1,uVar3,param_2[4],param_2[2],*param_2,iVar2 == 1);
    param_2[6] = uVar3;
    if ((iVar6 == 0x3fffffff) && (-1 < (int)((uint)*(ushort *)(param_1 + 0x2a) << 0x15))) {
      uVar3 = 1;
    }
    else {
      uVar3 = 0;
    }
    uVar7 = FUN_0004baf8(param_1);
    uVar1 = FUN_0004c924(param_1,0,0x83);
    uVar3 = FUN_00037f14(uVar7,uVar3,uVar1,uVar4,param_2[5],param_2[3],param_2[1],0);
    param_2[7] = uVar3;
    return;
  }
  FUN_0004a57a(param_2,0,0x20);
  return;
}

