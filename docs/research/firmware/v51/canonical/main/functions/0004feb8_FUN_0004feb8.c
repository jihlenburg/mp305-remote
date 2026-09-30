/* Address: 0004feb8; name: FUN_0004feb8; body bytes: 670 */

void FUN_0004feb8(int param_1,int param_2,int param_3,int param_4,uint param_5)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  byte bVar6;
  int iVar7;
  undefined1 auStack_d0 [88];
  undefined1 auStack_78 [88];
  
  puVar3 = auStack_d0;
  puVar5 = auStack_d0;
  iVar1 = FUN_0004bb48();
  iVar7 = *(int *)(iVar1 + 0x2c0);
  if (iVar7 == param_1) {
    return;
  }
  iVar2 = *(int *)(iVar1 + 0x2cc);
  if (iVar2 == param_1) {
    return;
  }
  if ((iVar2 != 0) && (iVar2 != iVar7)) {
    FUN_0003c97c(iVar2,0);
    FUN_0004e7c2(*(undefined4 *)(iVar1 + 0x2cc),0);
    FUN_0004e088(*(undefined4 *)(iVar1 + 0x2cc),0x5f,0);
    *(undefined4 *)(iVar1 + 0x2c8) = *(undefined4 *)(iVar1 + 0x2c0);
    iVar7 = *(int *)(iVar1 + 0x2cc);
    FUN_0005e210();
  }
  *(int *)(iVar1 + 0x2cc) = param_1;
  if ((*(int *)(iVar1 + 0x2c8) != 0) && ((int)((uint)*(byte *)(iVar1 + 0x2d4) << 0x1e) < 0)) {
    FUN_0004b3a0();
  }
  *(undefined4 *)(iVar1 + 0x2c8) = 0;
  if ((((param_2 == 10) || (param_2 == 0xb)) || (param_2 == 0xc)) ||
     ((param_2 == 0xd || (param_2 == 0xe)))) {
    bVar6 = 1;
  }
  else {
    bVar6 = 0;
  }
  *(byte *)(iVar1 + 0x2d4) = *(byte *)(iVar1 + 0x2d4) & 0xfc | bVar6 | (byte)((param_5 & 1) << 1);
  FUN_0003c97c(param_1,0);
  if (iVar7 != 0) {
    FUN_0003c97c(iVar7,0);
  }
  FUN_0004e7c2(param_1,0);
  if (iVar7 != 0) {
    FUN_0004e7c2(iVar7,0);
  }
  FUN_0004e088(param_1,0x5f,0);
  if (iVar7 != 0) {
    FUN_0004e088(iVar7,0x5f,0);
  }
  if (param_3 == 0 && param_4 == 0) {
    FUN_0005e210(param_1);
    if (param_5 == 0) {
      return;
    }
    if (iVar7 == 0) {
      return;
    }
    FUN_0004b3a0(iVar7);
    return;
  }
  FUN_0003c9f8(auStack_d0);
  FUN_0003cb2a(auStack_d0,param_1);
  FUN_0003cb12(auStack_d0,0x5e1eb);
  FUN_0003cadc(auStack_d0,0x5e187);
  FUN_0003caea(auStack_d0,param_3);
  FUN_0003cae0(auStack_d0,param_4);
  FUN_0003c9f8(auStack_78);
  FUN_0003cb2a(auStack_78,iVar7);
  FUN_0003caea(auStack_78,param_3);
  FUN_0003cae0(auStack_78,param_4);
  switch(param_2) {
  case 0:
    FUN_0003cafa(auStack_d0,0x5e7b5);
    iVar2 = 0;
    goto LAB_0005014a;
  case 1:
    FUN_0003cafa(auStack_d0,0x5e7b5);
    iVar1 = FUN_000408b0(iVar1);
    break;
  case 2:
    FUN_0003cafa(auStack_d0,0x5e7b5);
    iVar1 = FUN_000408b0(iVar1);
    goto LAB_00050090;
  case 3:
    FUN_0003cafa(auStack_d0,0x5e7bd);
    iVar1 = FUN_00040960(iVar1);
    break;
  case 4:
    FUN_0003cafa(auStack_d0,0x5e7bd);
    iVar1 = FUN_00040960(iVar1);
LAB_00050090:
    iVar1 = -iVar1;
    break;
  case 5:
    FUN_0003cafa(auStack_d0,0x5e7b5);
    uVar4 = FUN_000408b0(iVar1);
    FUN_0003cb1e(auStack_d0,uVar4,0);
  case 0xb:
    FUN_0003cafa(auStack_78,0x5e7b5);
    iVar2 = FUN_000408b0(iVar1);
    goto LAB_00050110;
  case 6:
    FUN_0003cafa(auStack_d0,0x5e7b5);
    iVar2 = FUN_000408b0(iVar1);
    FUN_0003cb1e(auStack_d0,-iVar2,0);
  case 0xc:
    FUN_0003cafa(auStack_78,0x5e7b5);
    iVar2 = FUN_000408b0(iVar1);
    goto LAB_000500e6;
  case 7:
    FUN_0003cafa(auStack_d0,0x5e7bd);
    uVar4 = FUN_00040960(iVar1);
    FUN_0003cb1e(auStack_d0,uVar4,0);
  case 0xd:
    FUN_0003cafa(auStack_78,0x5e7bd);
    iVar2 = FUN_00040960(iVar1);
LAB_00050110:
    iVar2 = -iVar2;
    goto LAB_000500e6;
  case 8:
    FUN_0003cafa(auStack_d0,0x5e7bd);
    iVar2 = FUN_00040960(iVar1);
    FUN_0003cb1e(auStack_d0,-iVar2,0);
  case 0xe:
    FUN_0003cafa(auStack_78,0x5e7bd);
    iVar2 = FUN_00040960(iVar1);
LAB_000500e6:
    iVar1 = 0;
LAB_0005015a:
    puVar3 = auStack_78;
    goto LAB_00050044;
  case 9:
    FUN_0003cafa(auStack_d0,&DAT_000583ed);
    iVar2 = 0xff;
LAB_0005014a:
    iVar1 = 0;
    puVar3 = auStack_d0;
    goto LAB_00050044;
  case 10:
    FUN_0003cafa(auStack_78,&DAT_000583ed);
    iVar2 = 0;
    iVar1 = 0xff;
    goto LAB_0005015a;
  default:
    goto switchD_0004fff0_default;
  }
  iVar2 = 0;
LAB_00050044:
  FUN_0003cb1e(puVar3,iVar1,iVar2);
switchD_0004fff0_default:
  if (iVar7 != 0) {
    FUN_0004e5a6(iVar7,0x2a,0);
    FUN_0003cb6c(auStack_d0);
    puVar5 = auStack_78;
  }
  FUN_0003cb6c(puVar5);
  return;
}

