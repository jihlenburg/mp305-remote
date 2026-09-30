/* Address: 000577c0; name: FUN_000577c0; body bytes: 562 */

void FUN_000577c0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  char *pcVar2;
  ushort uVar3;
  
  uVar3 = 3;
  if (DAT_1fffacac == '\0') {
    if (DAT_1fffacae == 3) {
      uVar1 = FUN_0004b9de(DAT_1ffe061c,0,param_3,param_4,param_4);
      uVar1 = FUN_0004b9de(uVar1,0);
      pcVar2 = "Passive Cable";
    }
    else if (DAT_1fffacae == 4) {
      uVar1 = FUN_0004b9de(DAT_1ffe061c,0,param_3,param_4,param_4);
      uVar1 = FUN_0004b9de(uVar1,0);
      pcVar2 = "Active Cable";
    }
    else {
      uVar1 = FUN_0004b9de(DAT_1ffe061c,0,param_3,param_4,param_4);
      uVar1 = FUN_0004b9de(uVar1,0);
      pcVar2 = " ";
    }
    FUN_000499de(uVar1,pcVar2);
  }
  else {
    if (1 < DAT_1fffacba) {
      uVar3 = DAT_1fffacba + 1 & 0xff;
    }
    uVar1 = FUN_0004b9de(DAT_1ffe061c,0,param_3,param_4,param_4);
    uVar1 = FUN_0004b9de(uVar1,0);
    FUN_000499de(uVar1,&DAT_00057a08,uVar3);
  }
  uVar1 = FUN_0004b9de(DAT_1ffe061c,1);
  uVar1 = FUN_0004b9de(uVar1,0);
  FUN_000499de(uVar1,"Undefined (0x%04x)",DAT_1fffacb0);
  if (DAT_1fffacb8 == 0) {
    if (DAT_1fffa0ce == '\x01') {
      uVar1 = FUN_0004b9de(DAT_1ffe061c,2);
      uVar1 = FUN_0004b9de(uVar1,0);
      pcVar2 = "%dV %dA %dW No-EPR";
    }
    else {
      uVar1 = FUN_0004b9de(DAT_1ffe061c,2);
      uVar1 = FUN_0004b9de(uVar1,0);
      pcVar2 = "%dV %dA\n%dW No-EPR";
    }
  }
  else if (DAT_1fffa0ce == '\x01') {
    uVar1 = FUN_0004b9de(DAT_1ffe061c,2);
    uVar1 = FUN_0004b9de(uVar1,0);
    pcVar2 = "%dV %dA %dW EPR";
  }
  else {
    uVar1 = FUN_0004b9de(DAT_1ffe061c,2);
    uVar1 = FUN_0004b9de(uVar1,0);
    pcVar2 = "%dV %dA\n%dW EPR";
  }
  FUN_000499de(uVar1,pcVar2,DAT_1fffacb4,DAT_1fffacb2);
  if (DAT_1fffacbc - 1U < 10) {
    uVar1 = FUN_0004b9de(DAT_1ffe061c,3);
    uVar1 = FUN_0004b9de(uVar1,0);
    FUN_000499de(uVar1,&DAT_00057aa8,*(undefined4 *)(&DAT_1ffe0300 + DAT_1fffacbc * 4));
  }
  else {
    uVar1 = FUN_0004b9de(DAT_1ffe061c,3);
    uVar1 = FUN_0004b9de(uVar1,0);
    FUN_000499de(uVar1,&DAT_00057a20);
  }
  if (DAT_1fffa0ce == '\x01') {
    switch(DAT_1fffacba) {
    case 0:
      uVar1 = FUN_0004b9de(DAT_1ffe061c,4);
      uVar1 = FUN_0004b9de(uVar1,0);
      pcVar2 = "USB2.0 only (480Mbps)";
      break;
    case 1:
      uVar1 = FUN_0004b9de(DAT_1ffe061c,4);
      uVar1 = FUN_0004b9de(uVar1,0);
      pcVar2 = "USB3.2 Gen1 (5Gbps)";
      break;
    case 2:
      goto switchD_0005792a_caseD_2;
    case 3:
      uVar1 = FUN_0004b9de(DAT_1ffe061c,4);
      uVar1 = FUN_0004b9de(uVar1,0);
      pcVar2 = "USB4 Gen3 (40Gbps)";
      break;
    case 4:
      uVar1 = FUN_0004b9de(DAT_1ffe061c,4);
      uVar1 = FUN_0004b9de(uVar1,0);
      pcVar2 = "USB4 Gen4 (80Gbps)";
      break;
    default:
      goto switchD_0005792a_default;
    }
  }
  else {
    switch(DAT_1fffacba) {
    case 0:
      uVar1 = FUN_0004b9de(DAT_1ffe061c,4);
      uVar1 = FUN_0004b9de(uVar1,0);
      pcVar2 = "USB2.0 only\n(480Mbps)";
      break;
    case 1:
      uVar1 = FUN_0004b9de(DAT_1ffe061c,4);
      uVar1 = FUN_0004b9de(uVar1,0);
      pcVar2 = "USB3.2 Gen1\n(5Gbps)";
      break;
    case 2:
switchD_0005792a_caseD_2:
      uVar1 = FUN_0004b9de(DAT_1ffe061c,4);
      uVar1 = FUN_0004b9de(uVar1,0);
      pcVar2 = "USB3.2/USB4 Gen2\n(10Gbps/20Gbps)";
      break;
    case 3:
      uVar1 = FUN_0004b9de(DAT_1ffe061c,4);
      uVar1 = FUN_0004b9de(uVar1,0);
      pcVar2 = "USB4 Gen3\n(40Gbps)";
      break;
    case 4:
      uVar1 = FUN_0004b9de(DAT_1ffe061c,4);
      uVar1 = FUN_0004b9de(uVar1,0);
      pcVar2 = "USB4 Gen4\n(80Gbps)";
      break;
    default:
switchD_0005792a_default:
      uVar1 = FUN_0004b9de(DAT_1ffe061c,4);
      uVar1 = FUN_0004b9de(uVar1,0);
      pcVar2 = " ";
    }
  }
  FUN_000499de(uVar1,pcVar2);
  return;
}

