/* Address: 0001cb8c; name: FUN_0001cb8c; body bytes: 178 */

void FUN_0001cb8c(undefined4 param_1)

{
  undefined *puVar1;
  undefined1 uVar2;
  undefined1 *extraout_r2;
  
  if (DAT_1fffab20 == '\0') {
switchD_0001cb9a_default:
    return;
  }
  switch(param_1) {
  case 0:
    uVar2 = 0;
    puVar1 = &UNK_0007aff0;
    break;
  case 1:
    uVar2 = 1;
    puVar1 = &UNK_0007b044;
    break;
  case 2:
    uVar2 = 2;
    puVar1 = &UNK_0007b050;
    break;
  case 3:
    uVar2 = 3;
    goto LAB_0001cbca;
  case 4:
    uVar2 = 4;
LAB_0001cbca:
    puVar1 = &UNK_0007b038;
    break;
  case 5:
    uVar2 = 5;
    puVar1 = &UNK_0007b064;
    break;
  case 6:
    uVar2 = 6;
    puVar1 = &UNK_0007b09c;
    break;
  case 7:
    uVar2 = 7;
    puVar1 = &UNK_0007b070;
    break;
  case 8:
    uVar2 = 8;
    puVar1 = &UNK_0007b0b4;
    break;
  case 9:
    uVar2 = 9;
    puVar1 = &UNK_0007b0c0;
    break;
  case 10:
    uVar2 = 10;
    puVar1 = &UNK_0007b0d8;
    break;
  case 0xb:
    uVar2 = 0xb;
    puVar1 = &UNK_0007b100;
    break;
  case 0xc:
    uVar2 = 0xc;
    puVar1 = &UNK_0007b110;
    break;
  case 0xd:
    uVar2 = 0xd;
    puVar1 = &UNK_0007afe4;
    break;
  case 0xe:
    uVar2 = 0xe;
    puVar1 = &UNK_0007b020;
    break;
  case 0xf:
    uVar2 = 0xf;
    puVar1 = &DAT_0007b02c;
    break;
  default:
    goto switchD_0001cb9a_default;
  }
  enter_critical();
  DAT_1fffa0a5 = 1;
  FUN_00012e00();
  *(undefined **)(extraout_r2 + 4) = puVar1;
  *(undefined **)(extraout_r2 + 8) = puVar1 + 8;
  *extraout_r2 = uVar2;
  exit_critical();
  return;
}

