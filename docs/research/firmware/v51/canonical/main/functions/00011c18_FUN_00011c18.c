/* Address: 00011c18; name: FUN_00011c18; body bytes: 528 */

void FUN_00011c18(int param_1)

{
  char cVar1;
  uint uVar2;
  short sVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  cVar1 = DAT_1fff9b9a;
  DAT_1fff9b34 = DAT_1fff9b34 + param_1;
  if (DAT_1fff9b34 < 0x2711) {
    if ((DAT_1fff9b34 < 5000) || (DAT_1ffe0194 != '\0')) {
      if (DAT_1fff9b34 < 5000) {
        DAT_1ffe0194 = '\0';
      }
    }
    else {
      DAT_1fff9bbe = 1;
      DAT_1ffe0194 = '\x01';
    }
  }
  else if (DAT_1fff9b91 != '\0') {
    FUN_00011864();
  }
  if (DAT_1fff9b96 == '\0') {
    if (cVar1 == '\x01') goto LAB_00011cc4;
  }
  else if (cVar1 == '\x01') {
    uVar5 = 1000;
    enter_critical();
    DAT_1fff9b96 = '\0';
    uVar6 = (uint)DAT_1fff9b94;
    exit_critical();
    DAT_1fff9bb4 = 0;
    for (uVar2 = 0; uVar2 < uVar6; uVar2 = uVar2 + 1 & 0xff) {
      uVar4 = ((uint)(ushort)(&DAT_1fff9b70)[uVar2] * (uint)(ushort)(&DAT_1fff9b60)[uVar2]) / 1000;
      if (uVar5 <= uVar4) {
        DAT_1fff9bb4 = (undefined1)uVar2;
        uVar5 = uVar4;
      }
    }
    DAT_1fff9ba8 = 0;
    DAT_1fff9bb0 = uVar5;
    goto LAB_00011cc4;
  }
  DAT_1fff9bb4 = 0;
  DAT_1fff9bb0 = 0;
LAB_00011cc4:
  if (DAT_1fff9b99 != '\0') {
    DAT_1fff9b99 = '\0';
    DAT_1fffaa28 = DAT_1fff9b9d;
    DAT_1fffaa29 = DAT_1fff9b9e;
    DAT_1fffaa26 = DAT_1fff9b9c;
    DAT_1fffaa0a = DAT_1fff9b54;
    DAT_1fffaa0c = DAT_1fff9b56;
    if (DAT_1fff9b9e < DAT_1fff9b9d) {
      DAT_1fffaa27 = DAT_1fff9b9d;
    }
    else {
      DAT_1fffaa27 = DAT_1fff9b9e;
    }
    if ((DAT_1fff9b9c < -0xf) && ('\x14' < DAT_1fffaa27)) {
      DAT_1fffaa26 = '\x05';
    }
    if (DAT_1fff9b34 < 0x2711) {
      DAT_1fffabbc = DAT_1fffabbc + 1;
    }
  }
  if (DAT_1fff9b98 != '\0') {
    DAT_1fff9b98 = '\0';
    DAT_1fff9bb9 = 1;
    FUN_0001ae38(1);
    DAT_1ffe018e = 0;
  }
  if (DAT_1fff9b97 != '\0') {
    DAT_1fff9b97 = '\0';
  }
  if (DAT_1fff9b9f != '\0') {
    DAT_1fff9b9f = '\0';
  }
  if (DAT_1fff9ba3 != '\0') {
    DAT_1fff9ba3 = '\0';
    DAT_1fff9baa = 3000;
    DAT_1fff9bac = 0;
    FUN_0001aebc(1);
    FUN_0001a5fc();
  }
  if (DAT_1fff9ba4 != '\0') {
    DAT_1fff9ba4 = '\0';
    DAT_1fffacac = DAT_1fff9b8f;
    DAT_1fffacae = DAT_1fff9b80;
    DAT_1fffacb0 = DAT_1fff9b82;
    if (DAT_1fff9b84 == 2) {
      DAT_1fffacb2 = 5;
    }
    else {
      DAT_1fffacb2 = 3;
    }
    if (DAT_1fff9b86 == 1) {
      DAT_1fffacb4 = 0x1e;
      sVar3 = 0x1c;
    }
    else if (DAT_1fff9b86 == 2) {
      DAT_1fffacb4 = 0x28;
      sVar3 = 0x24;
    }
    else if (DAT_1fff9b86 == 3) {
      DAT_1fffacb4 = 0x32;
      sVar3 = 0x30;
    }
    else {
      sVar3 = 0x14;
      DAT_1fffacb4 = 0x14;
    }
    DAT_1fffacb6 = sVar3 * DAT_1fffacb2;
    DAT_1fffacb8 = DAT_1fff9b8a;
    DAT_1fffacba = DAT_1fff9b8c;
    DAT_1fffacbc = DAT_1fff9b38;
    DAT_1fffaaeb = DAT_1fff9b90;
    if ((DAT_1fff9b90 == '\0') && (DAT_1fff9bac < 5)) {
      DAT_1fff9bac = DAT_1fff9bac + 1;
      DAT_1ffe018f = 0;
      DAT_1fff9baa = 3000;
    }
  }
  return;
}

