/* Address: ram:0004ec8c; name: FUN_ram_0004ec8c; body bytes: 256 */

void FUN_ram_0004ec8c(int param_1)

{
  undefined1 uVar1;
  char cVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  char acStack_54 [4];
  undefined1 auStack_50 [68];
  
  gp = 0x20004000;
  puVar3 = *(undefined1 **)(param_1 + 8);
  acStack_54[0] = '\0';
  uVar1 = *puVar3;
  switch(uVar1) {
  case 1:
  case 2:
    iVar4 = FUN_ram_0004e9c0(puVar3,auStack_50);
    if (iVar4 != 0x12) break;
    acStack_54[0] = '\x06';
    goto LAB_ram_0004ecd0;
  case 3:
    iVar4 = FUN_ram_0004eb9c(puVar3,auStack_50);
    break;
  case 4:
    iVar4 = FUN_ram_0004ebe2(puVar3,auStack_50);
    break;
  case 5:
    iVar4 = FUN_ram_0004ebc6(puVar3,auStack_50);
    break;
  case 6:
    iVar4 = FUN_ram_0004ead8(puVar3,auStack_50);
    break;
  case 7:
    iVar4 = FUN_ram_0004eb60(puVar3,auStack_50);
    break;
  case 8:
    iVar4 = FUN_ram_0004eb36(puVar3,auStack_50);
    break;
  case 9:
    iVar4 = FUN_ram_0004eb02(puVar3,auStack_50);
    break;
  case 10:
    iVar4 = FUN_ram_0004ec0c(puVar3,auStack_50);
    break;
  case 0xb:
    auStack_50[0] = puVar3[1];
    goto switchD_ram_0004ecbc_caseD_e;
  case 0xc:
    iVar4 = FUN_ram_0004ec36(puVar3,auStack_50);
    break;
  case 0xd:
    iVar4 = FUN_ram_0004ec62(puVar3,auStack_50);
    break;
  case 0xe:
    goto switchD_ram_0004ecbc_caseD_e;
  default:
    acStack_54[0] = '\a';
    goto LAB_ram_0004ecd0;
  }
  cVar2 = acStack_54[0];
  if (iVar4 == 0) {
switchD_ram_0004ecbc_caseD_e:
    iVar4 = FUN_ram_0004df14(*(undefined2 *)(param_1 + 2));
    cVar2 = '\b';
    if (iVar4 != 0) {
      puVar5 = DAT_ram_20001a70;
      if (*(char *)(iVar4 + 0xc) == '\b') {
        puVar5 = DAT_ram_20001a6c;
      }
      cVar2 = '\a';
      if ((puVar5 != (undefined4 *)0x0) && ((code *)*puVar5 != (code *)0x0)) {
        cVar2 = (*(code *)*puVar5)(iVar4,uVar1,auStack_50);
      }
    }
  }
  acStack_54[0] = cVar2;
  if (acStack_54[0] == '\0') {
    FUN_ram_0004e44a(*(undefined2 *)(param_1 + 2));
  }
  else {
LAB_ram_0004ecd0:
    FUN_ram_0004e7e6(*(undefined2 *)(param_1 + 2),acStack_54);
  }
  return;
}

