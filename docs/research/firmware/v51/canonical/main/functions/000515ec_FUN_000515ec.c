/* Address: 000515ec; name: FUN_000515ec; body bytes: 232 */

void FUN_000515ec(int param_1,uint param_2)

{
  byte bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  bool bVar8;
  
  switch(param_2) {
  default:
    goto switchD_000515f8_caseD_0;
  case 1:
    uVar2 = 0;
    break;
  case 2:
    uVar2 = 8;
    break;
  case 4:
    uVar2 = 1;
    break;
  case 8:
    uVar2 = 9;
  }
  FUN_0004e624(param_1,uVar2);
switchD_000515f8_caseD_0:
  uVar2 = FUN_00051512(param_1);
  uVar3 = FUN_0005150c(param_1);
  switch(param_2) {
  default:
    goto switchD_00051628_caseD_0;
  case 1:
  case 2:
    FUN_0004e654(uVar3);
    FUN_0004e63c(uVar3,1);
    FUN_0004e624(uVar2,1);
    FUN_0004e624(uVar3,1);
    FUN_0004e7f6(uVar3,0);
    uVar6 = 3;
    break;
  case 4:
  case 8:
    FUN_0004eae2(uVar3,&DAT_20000064);
    FUN_0004e63c(uVar3,1);
    FUN_0004e624(uVar2,0);
    FUN_0004e624(uVar3,0);
    FUN_0004e7f6(uVar3,3);
    uVar6 = 0;
  }
  FUN_0004e80c(uVar3,uVar6);
switchD_00051628_caseD_0:
  bVar1 = *(byte *)(param_1 + 0x30) & 0xc;
  if ((*(byte *)(param_1 + 0x30) & 0xc) != 0) {
    bVar1 = 1;
  }
  bVar8 = (param_2 & 0xc) != 0;
  if ((bool)bVar1 != bVar8) {
    FUN_0004bb48(param_1);
    iVar4 = FUN_0004089c();
    if (bVar8) {
      iVar5 = FUN_0004f078(100);
      iVar7 = iVar4 / 2;
      iVar4 = iVar5;
    }
    else {
      iVar7 = FUN_0004f078(100);
    }
    FUN_0004e84a(uVar2,iVar4,iVar7);
  }
  *(char *)(param_1 + 0x30) = (char)param_2;
  return;
}

